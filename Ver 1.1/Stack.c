#include<gtk/gtk.h>
#include<stdlib.h>
#include<stdio.h>

gint count =0;
char buf[5]="0";
int x=600;
GtkWidget **b;
GtkWidget *label[18];
int length=0;
char msg1[20]="Length exceeded!";
char msg2[30]="Nothing to dequeue!";

/* Function to open a dialog box displaying the message provided. */

void quick_message (gpointer frame, char message[]) 
{

	GtkWidget *dialog, *label, *content_area;
   
	/* Create the widgets */
   	dialog = gtk_dialog_new_with_buttons ("Error",
					 frame,                                         
               				 GTK_DIALOG_DESTROY_WITH_PARENT,
                                         GTK_STOCK_OK,
                                         GTK_RESPONSE_NONE,
                                         NULL);
   	content_area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));
   	label = gtk_label_new (message);
   	/* Ensure that the dialog box is destroyed when the user responds. */
   	g_signal_connect_swapped (dialog,
                             "response",
                             G_CALLBACK (gtk_widget_destroy),
                             dialog);
   	/* Add the label, and show everything we've added to the dialog. */
   	gtk_container_add (GTK_CONTAINER (content_area), label);
   	gtk_widget_show_all (dialog);
}


/*Func for label change on clicking + */
void increase(GtkWidget *widget, gpointer label)
{
	count++;

  	sprintf(buf, "%d", count);
  	gtk_label_set_text(GTK_LABEL(label), buf);
}

/*Func for label change when clicking - */
void decrease(GtkWidget *widget, gpointer label)
{
  	count--;

  	sprintf(buf, "%d", count);
  	gtk_label_set_text(GTK_LABEL(label), buf);
}

//Push function
int push_list(GtkWidget *widget, gpointer frame)
{

	if(length==9)
	{
		quick_message(frame,msg1);
		return 0;
	}
	if(length>0)
	{
		label[length+9]=gtk_label_new("  | ");
		gtk_fixed_put(GTK_FIXED(frame),label[length+9],430,x+40);
		
		label[length]=gtk_label_new("\\|/");
		gtk_fixed_put(GTK_FIXED(frame),label[length],430,x+50);
	
		gtk_widget_show(label[length]);
		gtk_widget_show(label[length+9]);
	}
	if(length>=0)
	{
		b[length]=gtk_button_new_with_label(buf);
		gtk_widget_set_size_request(b[length], 80,40);
		gtk_fixed_put(GTK_FIXED(frame), b[length], 400,x);
		x=x-70;
	
		gtk_widget_show(b[length]);
		length++;
		return 0;
	}
}

//Pop function
int pop_list(GtkWidget *widget, gpointer frame)
{
		length--;
		
		if(length<0)
		{
			quick_message(frame, msg2);
			length++;
			return 0;
		}
		if(length>=0)
		{
			gtk_widget_hide(b[length]);
			gtk_widget_hide(label[length]);
			gtk_widget_hide(label[length+9]);
			x=x+70;
			return 0;
		}
}

int main (int argc, char *argv[])
{
	GtkWidget *label;	//Calling up the widgets
	GtkWidget *window;
	GtkWidget *frame;
	GtkWidget *plus;
	GtkWidget *minus;
	GtkWidget *push;
	GtkWidget *pop;
	GtkWidget *label0;	// For the + - thing

	/*Initialisation for the push & pop fn*/
	b=(GtkWidget**)malloc(11*sizeof(GtkWidget));

	gtk_init(&argc, &argv);	//Start of GTK

	/*Setting up the window*/

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(window), 600, 650);
	gtk_window_set_title(GTK_WINDOW(window), "STACK");

	/*Setting up the frame*/

	frame = gtk_fixed_new();
	gtk_container_add(GTK_CONTAINER(window), frame);

	/*Creating buttons*/

	plus = gtk_button_new_with_label("+");
	gtk_widget_set_size_request(plus, 80,35);
	gtk_fixed_put(GTK_FIXED(frame), plus, 75, 350);

	minus = gtk_button_new_with_label("-");
	gtk_widget_set_size_request(minus, 80, 35);
	gtk_fixed_put(GTK_FIXED(frame), minus, 75, 410);
	
	push = gtk_button_new_with_label("PUSH");
	gtk_widget_set_size_request(push, 90,45);
	gtk_fixed_put(GTK_FIXED(frame), push, 125, 470);
        
	pop = gtk_button_new_with_label("POP");
        gtk_widget_set_size_request(pop, 90,45);
        gtk_fixed_put(GTK_FIXED(frame), pop, 125, 130);


	/*Creating labels*/

        label0 = gtk_label_new ("0");
        gtk_fixed_put(GTK_FIXED(frame), label0, 195,388);

	//Show command
	gtk_widget_show_all(window);

	/*destroy signal*/
	g_signal_connect(window, "destroy",
		G_CALLBACK(gtk_main_quit), NULL);

	/*If Button is clicked*/
	g_signal_connect(plus, "clicked", 
      		G_CALLBACK(increase), label0);

	g_signal_connect(minus, "clicked", 
      		G_CALLBACK(decrease), label0);

	g_signal_connect(push, "clicked",
        	G_CALLBACK(push_list), frame);

	g_signal_connect(pop, "clicked",
		G_CALLBACK(pop_list), frame);

	
	gtk_main();	//End of GTK function

	return 0;
}
