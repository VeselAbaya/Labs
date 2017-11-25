export class TaskModel {
  title: string;
  subTasks: Array<TaskModel>;
  complete: boolean;

  constructor(task: TaskModel) {
    if (task.title) { this.title = task.title; }
    else { throw new Error('Task\'s title is bad'); }
    this.complete = task.complete || false;
    this.subTasks = task.subTasks || [];
  }
}
