import {Injectable} from '@angular/core';
import {TaskModel} from '../models/task.model';

@Injectable()
export class TaskService {

  private tasks: Array<TaskModel> = [];

  constructor() {
    this.tasks = [
      new TaskModel({title: 'buy milk', complete: false, subTasks: []})
    ];
  }

  getTasks() {
    return this.tasks;
  }

  addTask(task: TaskModel) {
    if (task.title) {
      this.tasks.push(task);
    }
  }

  addSubTask(index: number, task: TaskModel) {
    if (task.title) {
      this.tasks[index].subTasks.push(task);
    }
  }
}
