#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "../../bmp.cpp"
#include "../../bmp_image24.cpp"
#include "../../bmp_exceptions.cpp"

#include <QDebug>
#define ALIGNMENT(width) ((4 - ((width)%4))%4)
MainWindow::MainWindow(QWidget *parent): QMainWindow(parent),
                                         ui(new Ui::MainWindow) {
    ui->setupUi(this);

    image = nullptr;
    compress_image = nullptr;
    this->setCentralWidget(ui->centralWidget);
    scene = new QGraphicsScene;
    scene_comress = new QGraphicsScene;
    image = nullptr;
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_actionOpen_triggered(){
    QString file_path = QFileDialog::getOpenFileName();
    if (file_path != "") {
        image = Bmp::bmp(file_path.toStdString());

        scene->clear();
        scene->addPixmap(QPixmap::fromImage(image->get_qImage()));
        ui->graphicsView->setScene(scene);
    }
}

#pragma pack(push, 1)
struct HSV {
    int h;
    double s;
    double v;
};
#pragma pack(pop)

bool operator ==(HSV const& a, HSV const& b) {
    double h_diff = std::abs(a.h - b.h);
    double s_diff = std::abs(a.s - b.s);
    double v_diff = std::abs(a.v - b.v);

    // percentage
    h_diff = h_diff / 360;

    double diff = (h_diff + s_diff + v_diff) / 3;
    if (diff <= DELTA) return true;
    else return false;
}

HSV make_HSV(QColor color) {
    HSV hsv;
    double red = color.red() / 255;
    double green = color.green() / 255;
    double blue = color.blue() / 255;

    double max = std::max(std::max(red, green), blue);
    double min = std::min(std::min(red, green), blue);
    double diff = max - min;

    if (max == min) {
        hsv.h = 0;
    } else if (red == max && green >= blue) {
        hsv.h = 60 * (green - blue) / diff;
    } else if (red == max && green < blue) {
        hsv.h = 60 * (green - blue) / diff + 360;
    } else if (green == max) {
        hsv.h = 60 * (blue - red) / diff + 120;
    } else if (blue == max) {
        hsv.h = 60 * (red - green) / diff + 240;
    }

    if (max == 0) {
        hsv.s = 0;
    } else {
        hsv.s = 1 - min/max;
    }

    hsv.v = max;

    return hsv;
}

void MainWindow::on_compress_button_clicked() {
    delete compress_image;

    compress_image = Bmp::copy(image);
    for (int y = 0; y != image->get_height(); ++y) {
        for (int x = 0; x != image->get_width(); ++x) {
            QColor color = image->get_color(x, y);
            int hue = color.toHsv().hue();
            int saturation = color.toHsv().saturation();
            int value = color.toHsv().value();
            for (int y_ = y; y_ != image->get_height(); ++y_) {
                for (int x_ = x; x_ != image->get_width(); ++x_) {
                    QColor color_ = image->get_color(x_, y_);
                    int hue_ = color_.toHsv().hue();
                    int saturation_ = color_.toHsv().saturation();
                    int value_ = color_.toHsv().value();
//                    qDebug() << hue << ":" << hue_ << saturation << ":" << saturation_ << value << ":" << value_;
//                    double diff = sqrt(((std::abs(hue - hue_))^2 + (std::abs(saturation - saturation_))^2 + (std::abs(value - value_))^2));
                    double diff = sqrt(((std::abs(hue - hue_)^2 + (saturation - saturation_)^2 + (value - value_)^2)));
                    if (diff <= 1) {
                        QColor avg{(color.red() + color_.red())/2,
                                   (color.green() + color_.green())/2,
                                   (color.blue() + color_.blue())/2};
                        compress_image->set_color(x, y, avg);
                        compress_image->set_color(x_, y_, avg);
                    }
                }
            }
        }
    }

    scene_comress->clear();
    scene_comress->addPixmap(QPixmap::fromImage(compress_image->get_qImage()));
    ui->graphicsView_compress->setScene(scene_comress);

    uint8_t* palette = new uint8_t[100000*4]{};
    int size = 0;
    for(int y = 0; y != image->get_height(); ++y) {
        for (int x = 0; x != image->get_width(); ++x) {
            QColor color = image->get_color(x, y);
            bool new_color = true;
            for (int i = 0; i != 256; ++i) {
                if (palette[i*4] == color.blue() &&
                        palette[i*4+1] == color.green() &&
                        palette[i*4+2] == color.red()) {
                    new_color = false;
                    break;
                }
            }

            if (new_color) {
                palette[size*4] = color.blue();
                palette[size*4+1] = color.green();
                palette[size*4+2] = color.red();
                ++size;
            }
        }
    } ++size;

    std::ofstream file(QFileDialog::getSaveFileName(this).toStdString(), std::ios::out | std::ios::binary);

    if (file.is_open()) {
        BitMapFileHeader bm_header;
        BitMapInfo       bm_info;

        bm_header.bfType1     = 'B';
        bm_header.bfType2     = 'M';
        bm_header.bfSize      = sizeof(BitMapFileHeader) +
                                sizeof(BitMapInfo) +
                                size/*palette.size()*/ * 4 +
                                (image->get_width() + ALIGNMENT(image->get_width())) * image->get_height(); // whole image size (headers + raster)
        bm_header.bfReserved1 = bm_header.bfReserved2 = 0;

        bm_info.biSize          = BI_SIZE;
        bm_info.biWidth         = image->get_width();
        bm_info.biHeight        = image->get_height();
        bm_info.biPlanes        = 1;
        bm_info.biCompression   = 0;
        bm_info.biSizeImage     = (image->get_width() + ALIGNMENT(image->get_width())) * image->get_height();
        bm_info.biXPelsPerMeter = 0;
        bm_info.biYPelsPerMeter = 0;
        bm_header.bfOffBits     = sizeof(BitMapFileHeader) +
                                  sizeof(BitMapInfo) +
                                  size/*palette.size()*/ * 4;
        bm_info.biBitCount      = 8;
        bm_info.biClrUsed       = size/*palette.size()*/;
        bm_info.biClrImportant  = 0;

        file.write(reinterpret_cast<char*>(&bm_header), sizeof(BitMapFileHeader));
        file.write(reinterpret_cast<char*>(&bm_info), sizeof(BitMapInfo));
        file.write(reinterpret_cast<char*>(palette), size * 4);

        // allocation memory for new image
        uint8_t** saving_raster = new uint8_t*[bm_info.biHeight];
        saving_raster[0] = new uint8_t[bm_info.biHeight * ((bm_info.biWidth) + ALIGNMENT(bm_info.biWidth))]{};
        for (int i = 1; i != bm_info.biHeight; ++i) {
            saving_raster[i] = saving_raster[i-1] + (bm_info.biWidth) + ALIGNMENT(bm_info.biWidth);
        }


        for (int x = 0; x != bm_info.biWidth; ++x) {
            for (int y = 0; y != bm_info.biHeight; ++y) {
                QColor color = image->get_color(x, y);
                for (int i = 0; i != 256; ++i) {
                    if (palette[i*4] == color.blue() &&
                            palette[i*4+1] == color.green() &&
                            palette[i*4+2] == color.red()) {
                        saving_raster[bm_info.biHeight - y - 1][x] = i;
                    }
                }
            }
        }

        file.write(reinterpret_cast<char*>(saving_raster[0]),
                                           bm_info.biHeight * ((bm_info.biWidth) + ALIGNMENT(bm_info.biWidth)));
        file.close();

        delete [] saving_raster[0];
        delete [] saving_raster;
    }
  
  //    std::ofstream file(QFileDialog::getSaveFileName(this).toStdString(), std::ios::out | std::ios::binary);

//    if (file.is_open()) {
//        BitMapFileHeader bm_header;
//        BitMapInfo       bm_info;

//        bm_header.bfType1     = 'B';
//        bm_header.bfType2     = 'M';
//        bm_header.bfSize      = sizeof(BitMapFileHeader) +
//                                sizeof(BitMapInfo) +
//                                palette.size() +
//                                (image->get_width() + ALIGNMENT(image->get_width())) * image->get_height(); // whole image size (headers + raster)
//        bm_header.bfReserved1 = bm_header.bfReserved2 = 0;

//        bm_info.biSize          = BI_SIZE;
//        bm_info.biWidth         = image->get_width();
//        bm_info.biHeight        = image->get_height();
//        bm_info.biPlanes        = 1;
//        bm_info.biCompression   = 0;
//        bm_info.biSizeImage     = (image->get_width() + ALIGNMENT(image->get_width())) * image->get_height();
//        bm_info.biXPelsPerMeter = 0;
//        bm_info.biYPelsPerMeter = 0;
//        bm_header.bfOffBits     = sizeof(BitMapFileHeader) +
//                                  sizeof(BitMapInfo) +
//                                  palette.size();
//        bm_info.biBitCount      = 8;
//        bm_info.biClrUsed       = palette.size();
//        bm_info.biClrImportant  = 0;

//        file.write(reinterpret_cast<char*>(&bm_header), sizeof(BitMapFileHeader));
//        file.write(reinterpret_cast<char*>(&bm_info), sizeof(BitMapInfo));
//        file.write(reinterpret_cast<char*>(palette.data()), palette.size());

//        // allocation memory for new image
//        uint8_t** saving_raster = new uint8_t*[bm_info.biHeight];
//        saving_raster[0] = new uint8_t[bm_info.biHeight * ((bm_info.biWidth) + ALIGNMENT(bm_info.biWidth))]{};
//        for (int i = 1; i != bm_info.biHeight; ++i) {
//            saving_raster[i] = saving_raster[i-1] + (bm_info.biWidth) + ALIGNMENT(bm_info.biWidth);
//        }


//        for (int x = 0; x != bm_info.biWidth; ++x) {
//            for (int y = 0; y != bm_info.biHeight; ++y) {
//                QColor color = image->get_color(x, y);
//                for (int i = 0; i != palette.size()/4; ++i) {
//                    if (palette[i*4] == color.blue() &&
//                            palette[i*4+1] == color.green() &&
//                            palette[i*4+2] == color.red()) {
//                        saving_raster[bm_info.biHeight - y - 1][x] = i;
//                    }
//                }
//            }
//        }

//        file.write(reinterpret_cast<char*>(saving_raster[0]),
//                                           bm_info.biHeight * ((bm_info.biWidth) + ALIGNMENT(bm_info.biWidth)));
//        file.close();

//        delete [] saving_raster[0];
//        delete [] saving_raster;
//    }
}

