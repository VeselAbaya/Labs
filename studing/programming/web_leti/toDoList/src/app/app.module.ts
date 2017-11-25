import {BrowserModule} from '@angular/platform-browser';
import {NgModule} from '@angular/core';

import {AppComponent} from './app.component';
import {TasksComponent } from './components/tasks/tasks.component';
import {TaskService} from './services/task.service';
import {FormsModule, ReactiveFormsModule} from '@angular/forms';
import {AddFormComponent} from './components/add-form/add-form.component';
import {AddSubTaskComponent} from "./components/addSubTask-form/addSubTask-form.component"; //Заимпортировал и теперь при нажатии на enter
                                              //срабатывает add-form;

@NgModule({
  declarations: [
    AppComponent,
    TasksComponent,
    AddFormComponent,
    AddSubTaskComponent
  ],
  imports: [
    BrowserModule, FormsModule, ReactiveFormsModule
  ],
  providers: [TaskService],
  bootstrap: [AppComponent]
})
export class AppModule { }
