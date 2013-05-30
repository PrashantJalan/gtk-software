#include <gtk/gtk.h>
#include <stdlib.h>

gint count=0;
char buf[5]="0";
GtkWidget** b;
GtkWidget *label[11];
int length=0;
int x=20;
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
void increase(GtkWidget *widget, gpointer label0)
{
	count++;

  	sprintf(buf, "%d", count);
  	gtk_label_set_text(GTK_LABEL(label0), buf);
}

/*Func for label change when clicking - */
void decrease(GtkWidget *widget, gpointer label0)
{
  	count--;

  	sprintf(buf, "%d", count);
  	gtk_label_set_text(GTK_LABEL(label0), buf);
}

int queue_list(GtkWidget *widget, gpointer frame)
{
	if (length==11)
	{
		quick_message(frame,msg1);
		return 0;		
	}
	if (length>0)
	{
		label[length] = gtk_label_new ("<--");
		gtk_fixed_put(GTK_FIXED(frame), label[length], x-25, 60);
		gtk_widget_show(label[length]);
	}
	if (length>=0)
	{	
        b[length] = gtk_button_new_with_label(buf);
        gtk_widget_set_size_request(b[length], 40,40);
        gtk_fixed_put(GTK_FIXED(frame), b[length], x, 50);
	
	x=x+70;
	gtk_widget_show(b[length]);
	length++;
	}
	return 0;
}

int  dequeue_list(GtkWidget *widget, gpointer frame)
{
	if (length<12)
		gtk_widget_hide(label[length-1]);
	if(length==1)	
        {
		gtk_widget_hide(b[0]);
		b[1]=NULL;
		length--;
		x=x-70;
		return 0;
	}
	else if(length>1)
	{ 
		gtk_widget_hide(b[0]);
		b[0]=b[1];
		x=20;
		int i;
		for(i=1;i<=length;i++)
		{
			gtk_fixed_put(GTK_FIXED(frame), b[i], x, 50);
			b[i]=b[i+1];
			x=x+70;
		}
		x=x-70;
		b[length]=NULL;
		length--;
		return 0;
	}	
	else
	{
		quick_message(frame, msg2);
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
	GtkWidget *queue;
	GtkWidget *dequeue;
	GtkWidget *label0;	// For the + - thing

	gtk_init(&argc, &argv);	//Start of GTK

	/*Some initialisations for the queue and dequeue function */

	b=(GtkWidget**)malloc(20*sizeof(GtkWidget));


	/*Setting up the window*/

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(window), 780, 400);
	gtk_window_set_title(GTK_WINDOW(window), "Queue");


	/*Setting up the frame*/

	frame = gtk_fixed_new();
	gtk_container_add(GTK_CONTAINER(window), frame);


	/*Creating buttons*/

	plus = gtk_button_new_with_label("+");
	gtk_widget_set_size_request(plus, 80,35);
	gtk_fixed_put(GTK_FIXED(frame), plus, 75, 170);

	minus = gtk_button_new_with_label("-");
	gtk_widget_set_size_request(minus, 80, 35);
	gtk_fixed_put(GTK_FIXED(frame), minus, 75, 230);

	label0 = gtk_label_new ("0");
	gtk_fixed_put(GTK_FIXED(frame), label0, 195, 208);
	

	/*Queue and dequeue button*/

	queue = gtk_button_new_with_label("Queue");
	gtk_widget_set_size_request(queue, 90,45);
	gtk_fixed_put(GTK_FIXED(frame), queue, 125, 290);
        
	dequeue = gtk_button_new_with_label("Dequeue");
        gtk_widget_set_size_request(dequeue, 90,45);
        gtk_fixed_put(GTK_FIXED(frame), dequeue, 295, 290);


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
        
	g_signal_connect(queue, "clicked",
        	G_CALLBACK(queue_list), frame);

	g_signal_connect(dequeue, "clicked",
		G_CALLBACK(dequeue_list), frame);

	gtk_main();	//End of GTK function

	return 0;
}


