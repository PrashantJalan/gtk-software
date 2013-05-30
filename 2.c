#include<gtk/gtk.h>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>


void callback(GtkWidget *widget, gpointer plus)
{
	GdkColor color;
	
	gdk_color_parse ("orange", &color);
	gtk_widget_modify_bg ( GTK_WIDGET(plus), GTK_STATE_NORMAL, &color);

	sleep(2);

//	gtk_widget_modify_bg ( GTK_WIDGET(plus), GTK_STATE_NORMAL, NULL);
}
int main (int argc, char *argv[])
{
	GtkWidget *window;
	GtkWidget *frame;
	GtkWidget *plus;

	gtk_init(&argc,&argv);	//Start of GTK
	
	/*Setting up the window*/

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(window), 1200, 600);
	gtk_window_set_title(GTK_WINDOW(window), "BINARY TREE");
	
	
	/*Setting up the frame*/

	frame = gtk_fixed_new();
	gtk_container_add(GTK_CONTAINER(window), frame);


	/*Creating buttons*/

	plus = gtk_button_new_with_label("+");
	gtk_widget_set_size_request(plus, 80,35);
	gtk_fixed_put(GTK_FIXED(frame), plus, 40, 50);

	gtk_widget_show_all(window);
	

	g_signal_connect(plus,"clicked",
			G_CALLBACK(callback), plus);	
	
	gtk_main();
}