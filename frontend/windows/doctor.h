#include "../gtkInjector.h"

#include <gtk/gtk.h>

typedef enum{
  D_T_ID,
  D_T_NAME,
  D_T_BLOODTYPE,
  D_T_DONATIONDATE,
  D_T_ACTION,
  D_T_NUM_COLUMNS
} Doctor_Column_type;


GtkTreeView *treead;
GtkTreeModel *modelad;
GtkWidget *insert_button;
GtkWidget *delete_button;
GtkWidget *modify_button;
GtkWidget *logout_button;
GtkTreeSelection *selection;

static GtkTreeModel *create_and_fill_doctor_model (void) {
  GtkListStore *store;
  GtkTreeIter iter;

  store=gtk_list_store_new (5, G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);

  gtk_list_store_append(store,&iter);
  gtk_list_store_set (store, &iter,
      D_T_ID, "1",
      D_T_NAME, "Nana",
      D_T_BLOODTYPE,"A+",
      D_T_DONATIONDATE, "15.11.2020",
      D_T_ACTION, "Approved",
      -1);

  return GTK_TREE_MODEL (store);
}

//Insert button clicked
// static void insert_clicked(void){
// 	modelad = append_element();
// 	gtk_tree_view_set_model (GTK_TREE_VIEW (treead), modelad);
// }
//Delete button clicked
// static void delete_clicked(void){
	
// 	GtkTreeIter iter1;

// 	selection=gtk_tree_view_get_selection(GTK_TREE_VIEW (treead));
// 	gtk_tree_selection_set_mode(GTK_TREE_SELECTION(selection),GTK_SELECTION_SINGLE);
// 	if(gtk_tree_selection_get_selected(selection,&modelad,&iter1)){
// 	gtk_list_store_remove(GTK_LIST_STORE(modelad),&iter1);}
// }

static void onAdminLoginClicked(void) {
	gtk_widget_hide(doctorWindow);
  gtk_widget_show(initialWindow);
}

void initDoctorWindow() {
  doctorWindow = GTK_WIDGET(gtk_builder_get_object(builder, "doctor_page"));

  treead=GTK_WIDGET(gtk_builder_get_object(builder,"treeview1"));

	insert_button=GTK_WIDGET(gtk_builder_get_object(builder,"insert_doctor_button"));
	delete_button=GTK_WIDGET(gtk_builder_get_object(builder,"delete_doctor_button"));
	
	logout_button=GTK_WIDGET(gtk_builder_get_object(builder,"doctor_logout"));

  GtkTreeViewColumn *column1=gtk_tree_view_column_new_with_attributes("ID",gtk_cell_renderer_text_new (),"text",D_T_ID,NULL);  
  GtkTreeViewColumn *column2=gtk_tree_view_column_new_with_attributes("Name",gtk_cell_renderer_text_new (),"text",D_T_NAME,NULL);  
	GtkTreeViewColumn *column3=gtk_tree_view_column_new_with_attributes("Blood Type",gtk_cell_renderer_text_new (),"text",D_T_BLOODTYPE,NULL);
	GtkTreeViewColumn *column4=gtk_tree_view_column_new_with_attributes("Donation date",gtk_cell_renderer_text_new (),"text",D_T_DONATIONDATE,NULL);
	GtkTreeViewColumn *column5=gtk_tree_view_column_new_with_attributes("Action",gtk_cell_renderer_text_new (),"text",D_T_ACTION,NULL);

	gtk_tree_view_column_set_expand(column1,TRUE);
	gtk_tree_view_column_set_expand(column2,TRUE);
	gtk_tree_view_column_set_expand(column3,TRUE);
	gtk_tree_view_column_set_expand(column4,TRUE);
	gtk_tree_view_column_set_expand(column5,TRUE);

	gtk_tree_view_append_column (GTK_TREE_VIEW (treead), column1);
	gtk_tree_view_append_column (GTK_TREE_VIEW (treead), column2);
	gtk_tree_view_append_column (GTK_TREE_VIEW (treead), column3);
	gtk_tree_view_append_column (GTK_TREE_VIEW (treead), column4);
	gtk_tree_view_append_column (GTK_TREE_VIEW (treead), column5);


	modelad = create_and_fill_doctor_model();
	gtk_tree_view_set_model (GTK_TREE_VIEW (treead), modelad);

	g_signal_connect(logout_button, "clicked", G_CALLBACK(onAdminLoginClicked),NULL);
	// g_signal_connect(delete_button, "clicked", G_CALLBACK(delete_clicked),NULL);
}
