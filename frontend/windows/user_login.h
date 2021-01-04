#include "../gtkInjector.h"
#include "../socket/socketInjector.h"

#include <gtk/gtk.h>

#include "../../shared/entities/entities.h"
#include "../../shared/routes.h"

GtkEntry *userLoginPhoneInput;
GtkEntry *userLoginPasswordInput;
GtkWidget *button;
GtkWidget *registerButton;

static void on_user_register_button_clicked(void) {
	gtk_widget_hide(userLoginWindow);
	gtk_widget_show(userRegistrationWindow);
}

static void on_user_login_button_clicked(void) {
  const char* phone = gtk_entry_get_text(userLoginPhoneInput);
  const char* pass = gtk_entry_get_text(userLoginPasswordInput);

  printf("Phone: %s\n", phone);
  printf("Password: %s\n", pass);

  struct Request request;
  struct Response response;

  sprintf(request.route.module, AUTH_MODULE);
  sprintf(request.route.method, USER_LOGIN_METHOD);

  sprintf(request.phoneNumber, "%s", phone);
  sprintf(request.password, "%s", pass);

  sendAll(socketClientId, &request, sizeof(request), 0);

  recv(socketClientId, &response, sizeof(response), MSG_WAITALL);

  printf("[LOGIN] Status: %d", response.status);
  printf("[LOGIN] name: %s", response.data.user.name);
}

void initUserLoginWindow() {
  userLoginWindow = GTK_WIDGET(gtk_builder_get_object(builder, "user_login"));

  userLoginPhoneInput = GTK_ENTRY(gtk_builder_get_object(builder, "user_phone"));
  userLoginPasswordInput = GTK_ENTRY(gtk_builder_get_object(builder, "password"));
  button = GTK_WIDGET(gtk_builder_get_object(builder,"Login_button"));
  registerButton = GTK_WIDGET(gtk_builder_get_object(builder,"reg_btn"));

  g_signal_connect(button, "clicked", G_CALLBACK(on_user_login_button_clicked), NULL);
  g_signal_connect(registerButton, "clicked", G_CALLBACK(on_user_register_button_clicked), NULL);
}
