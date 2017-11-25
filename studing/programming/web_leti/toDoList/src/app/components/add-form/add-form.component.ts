import {Component} from '@angular/core';
import {TaskService} from '../../services/task.service';
import {FormArray, FormControl, FormGroup, Validators} from '@angular/forms';
import {TaskModel} from '../../models/task.model';

@Component({
  selector: 'addForm',
  templateUrl: 'add-form.component.html',
  styleUrls: ['add-form.component.css']
})

export class AddFormComponent {
  constructor(private taskService: TaskService) {}

  get subTasks(): FormArray { return this.addForm.get('subTasks') as FormArray; }

  addForm: FormGroup = new FormGroup({
    addTask: new FormControl('', Validators.required),
    subTasks: new FormArray([])
  });

  add(formGroup: FormGroup) {
    const subTasksFormLenght = this.subTasks.length;

    const task: TaskModel = new TaskModel({title: formGroup.get('addTask').value,
                                           complete: false,
                                           subTasks: []});

    for (let i = 0; i !== subTasksFormLenght; ++i) {
      console.log(this.subTasks.at(i).value);
      task.subTasks[i] = new TaskModel({title: this.subTasks.at(i).value,
                                        complete: false,
                                        subTasks: []});
    }

    this.taskService.addTask(task);

    this.addForm.reset();
  }

  addSubTaskForm() {
    this.subTasks.push(new FormControl('', Validators.required));
  }

  removeSubTaskForm(index: number) {
    this.subTasks.removeAt(index);
  }
}
