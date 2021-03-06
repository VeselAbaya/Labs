#ifndef INFO_DIALOG_H
#define INFO_DIALOG_H

#include <memory>

#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include <bmp.h>

/*! \class Info_dialog
 * \brief Class for implementation of dialog
 * with information about image */
class Info_dialog: public QDialog {
    Q_OBJECT

public:
    /*! Constructor
     * \param image Bmp image */
    explicit Info_dialog(Bmp_image const* image);
    ~Info_dialog();

public slots:
    /*! Method to change info according to image */
    void change_info(Bmp_image const* image);

    /*! Static Method to make size more human readable
     * \param size (in bytes)
     * \return QString width good implementation */
    static QString make_beauty(int size);

private:
    QLabel* width;    /*!< Image width */
    QLabel* height;   /*!< Image height */
    QLabel* size;     /*!< Image size */
    QLabel* bitcount; /*!< Image bitcount */
};

#endif // INFO_DIALOG_H
