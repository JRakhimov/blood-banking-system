#include "../gtkInjector.h"
#include "../../shared/entities/entities.h"

#include <gtk/gtk.h>

GtkEntry *userRegistrationPhoneInput;
GtkEntry *userRegistrationDoBInput;
GtkEntry *userRegistrationPasswordInput;
GtkEntry *userRegistrationNameInput;
GtkWidget *button;

static void on_btn_reg_clicked(void) {
  const char* phone = gtk_entry_get_text(userRegistrationPhoneInput);
  const char* birth = gtk_entry_get_text(userRegistrationDoBInput);
  const char* pass = gtk_entry_get_text(userRegistrationPasswordInput);
  const char* name = gtk_entry_get_text(userRegistrationNameInput);

  if (strlen(phone) == 0 || strlen(pass) == 0 || strlen(birth) == 0) {
    return;
  }

  printf("Username:%s\n", phone);
  printf("Birth_date:%s\n", birth);
  printf("Password:%s\n", pass);
  printf("Name:%s\n", name);

  struct Request request;
  struct Response response;

  sprintf(request.route.module, AUTH_MODULE);
  sprintf(request.route.method, USER_REGISTRATION_METHOD);

  sprintf(request.phoneNumber, "%s", phone);
  sprintf(request.password, "%s", pass);
  sprintf(request.date, "%s", birth);
  sprintf(request.name, "%s", name);
  sprintf(request.bloodType, "A+");
  sprintf(request.validStatus, "pending");

  sendAll(socketClientId, &request, sizeof(request), 0);
  recv(socketClientId, &response, sizeof(response), MSG_WAITALL);

  printf("[REGISTRATION] Status: %d\n", response.status);
}

void initUserRegistrationWindow() {
  userRegistrationWindow = GTK_WIDGET(gtk_builder_get_object(builder, "user_registration"));

  userRegistrationPhoneInput = GTK_ENTRY(gtk_builder_get_object(builder, "user_reg_phone"));
  userRegistrationPasswordInput = GTK_ENTRY(gtk_builder_get_object(builder, "reg_psw_entry"));
  userRegistrationDoBInput = GTK_ENTRY(gtk_builder_get_object(builder, "date_of_birth"));
  userRegistrationNameInput = GTK_ENTRY(gtk_builder_get_object(builder, "reg_name"));
  button=GTK_WIDGET(gtk_builder_get_object(builder,"btn_reg"));

  g_signal_connect(button, "clicked", G_CALLBACK(on_btn_reg_clicked),NULL);
}


