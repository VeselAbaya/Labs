import {Component, Input} from '@angular/core';
import {TaskService} from '../../services/task.service';
import {FormArray, FormGroup, FormControl, Validators} from '@angular/forms';

@Component({
  selector: 'addSubTaskForm',
  templateUrl: 'addSubTask-form.component.html',
  styleUrls: ['addSubTask-form.component.css']
})

export class AddSubTaskComponent {
  @Input() taskIndex: number = null;

  constructor(private taskService: TaskService) {}

  get subTasks(): FormArray { return this.addSubTaskForm.get('subTasks') as FormArray; }

  addSubTaskForm: FormGroup = new FormGroup({
    'subTasks': new FormArray([
      new FormControl('', Validators.required)
    ])
  });

  addForm() {
    this.subTasks.push(new FormControl('', Validators.required));
  }

  addSubTask(taskIndex: number, index: number) { // index - индекс формы в subTasks
    if (this.subTasks.at(index).value) {
      this.taskService.addSubTask(taskIndex, {title: this.subTasks.at(index).value,
                                                   complete: false,
                                                   subTasks: []});
      this.subTasks.removeAt(index);
    }
  }
}
