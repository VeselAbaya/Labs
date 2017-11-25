import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';

import { AppComponent } from './app.component';
import { AppHeaderComponent } from './components/app-header/app-header.component';
import { UnauthorizedPageComponent } from './components/unathorized-page/unathorized-page.component';
import { AuthorizedPage1Component } from './components/authorized-page-1/authorized-page-1.component';
import { AuthorizedPage2Component } from './components/authorized-page-2/authorized-page-2.component';
import {RouterModule} from '@angular/router';
import {AuthService} from "./services/auth.service";
import {AuthGuard} from "./services/auth.guard";

@NgModule({
  declarations: [
    AppComponent,
    AppHeaderComponent,
    UnauthorizedPageComponent,
    AuthorizedPage1Component,
    AuthorizedPage2Component
  ],
  imports: [
    BrowserModule,
    RouterModule.forRoot([
      {
        path: '',
        component: UnauthorizedPageComponent
      },
      {
        path: 'page1',
        component: AuthorizedPage1Component,
        canActivate: [AuthGuard]
      },
      {
        path: 'page2',
        component: AuthorizedPage2Component,
        canActivate: [AuthGuard]
      },
      {
        path: '**',
        redirectTo: '',
      }
    ])
  ],
  providers: [AuthService, AuthGuard],
  bootstrap: [AppComponent]
})
export class AppModule { }
