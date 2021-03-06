/********************************
Project: Debug Station
Lead Programmer: Jacob Hegna
Code is property of FRC Team 2410
********************************/

#include "headers/headers.h"

//This is just to make sure that the
//defaults are 0 and not some crazy
//number.  If you want to change the
//defaults, change the defaults.xml
//file.
float values[6] = { 0.f,   //point 1
                    0.f,   //point 2
                    0.f,   //point 3
                    0.f,   //point 4
                    0.f,   //point 5
                    0.f }; //point 6

float control_values[6] = { 0.5f,   //point 1
                            0.5f,   //point 2
                            0.5f,   //point 3
                            0.5f,   //point 4
                            0.5f,   //point 5
                            0.5f }; //point 6

float winWidth, winHeight;

float xrot = 0.f;
float yrot = 0.f;

float xrotStep = 1.f;
float yrotStep = 1.f;

std::string portFromFile;

int control_value_select = 3;

Socket sendValues;

void init()
{
	glutInitDisplayMode( GLUT_DOUBLE );
	glutInitWindowSize( 1200, 600 );
	glutInitWindowPosition( 0, 0 );
	glutCreateWindow( "Team 2410 Debug Station" );

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    //glOrtho( 0.0, 400, 600, 0.0, 1.0, -1.0 );

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
	
	glEnable(GL_POINT_SMOOTH);
	glPointSize(10.f);

	glEnable(GL_TEXTURE_2D);

    ilInit();
    ilClearColour( 255, 255, 255, 000 );
}

bool init_values(std::string filename)
{
    Parser vertex_data(filename); //load the file into the class instance
    if(vertex_data.test_file() == true) //if the file cannot be opened
    {
        int num_of_tags = vertex_data.init_tags();
        vertex_data.load_tags();
        vertex_data.load_data();

        Tag_Data *tag_data = vertex_data.retrieve_data();

        for(int i = 0; i < num_of_tags; i++)
        {
            if(tag_data[i].tag == "one")
            {
                values[0] = atof(tag_data[i].data.c_str());
            }
            if(tag_data[i].tag == "two")
            {
                values[1] = atof(tag_data[i].data.c_str());
            }
            if(tag_data[i].tag == "three")
            {
                values[2] = atof(tag_data[i].data.c_str());
            }
            if(tag_data[i].tag == "four")
            {
                values[3] = atof(tag_data[i].data.c_str());
            }
            if(tag_data[i].tag == "five")
            {
                values[4] = atof(tag_data[i].data.c_str());
            }
            if(tag_data[i].tag == "six")
            {
                values[5] = atof(tag_data[i].data.c_str());
            }
			
			if(tag_data[i].tag == "xrot")
			{
				xrot = atof(tag_data[i].data.c_str());
			}
			if(tag_data[i].tag == "yrot")
			{
				yrot = atof(tag_data[i].data.c_str());
			}

			if(tag_data[i].tag == "xrotStep")
			{
				xrotStep = atof(tag_data[i].data.c_str());
			}
			if(tag_data[i].tag == "yrotStep")
			{
				yrotStep = atof(tag_data[i].data.c_str());
			}
            if(tag_data[i].tag == "recPort")
            {
                portFromFile = tag_data[i].data;
            }
        }
    } else {
        return false;
    }

    return true;
}

void main_loop()
{
    glutDisplayFunc(render);
    glutIdleFunc(render);
    glutReshapeFunc(reshape);

	glutKeyboardFunc(keyPressed);
    glutKeyboardUpFunc(keyUp);
    glutSpecialFunc(specialKeyPressed);
    glutSpecialUpFunc(specialKeyUp); 

	glutMainLoop(); //Enter gluts main loop
}

static void* networking_listen_entry(void* param)
{
    Socket socket("2410", false, NULL);
	socket.listen();
}

static void* moar_values(void *param)
{
	float xtra_values[6] = {0, 0, 0, 0, 0, 0};
	
	while(true)
	{
		for(int i = 0; i < 6; i++)
		{
			printf("%i: %f\n", i, xtra_values[i]);
		}

 		sleep(1);

		printf("\033[1J\033[12A");
	}
}

int main(int argc, char* args[])
{

    //AllocConsole();
    //freopen("CONOUT$", "a", stdout);

    //Initialize our vertices based off of the XML file
    init_values("resources/defaults.xml");

    //Start our networking thread
    pthread_t thread;
    int rc;
    rc = pthread_create(&thread, NULL, networking_listen_entry, (void*)NULL); //Create the thread

    sendValues.init("2410", true, "192.168.0.1");

    //Initialize our Libraries
    glutInit(&argc, args);
    init();

    //Start the Program
    main_loop();

    pthread_cancel(thread);

    //Wait until the networking thread exits
    pthread_exit(NULL);

    return 0;
}
