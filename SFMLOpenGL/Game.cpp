#include <Game.h>
#include <iostream>
#include <fstream>
#include <string>

static bool flip;

std::string readFromFile(std::string filePath)
{
	std::string r;
	std::string line;
	ifstream file(filePath);
	if (file.is_open())
	{
		while (getline(file, line))
		{
			r += line;
			r += "\n";
		}
	}
	else
	{
		DEBUG_MSG("Unable to read the file " + filePath);
	}
	return r;
}

Game::Game() : window(VideoMode(800, 600), "OpenGL Cube Vertex and Fragment Shaders")
{

}

Game::~Game() {}

void Game::run()
{

	initialize();

	Event event;

	while (isRunning) {

#if (DEBUG >= 2)
		DEBUG_MSG("Game running...");
#endif

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				isRunning = false;
			}
		}
		update();
		render();
	}

}

typedef struct
{
	float coordinate[3];
	float color[4];
} Vertex;

Vertex vertex[6];
GLubyte triangles[6];

/* Variable to hold the VBO identifier and shader data */
GLuint	index, //Index to draw
		vsid, //Vertex Shader ID
		fsid, //Fragment Shader ID
		progID, //Program ID
		vbo = 1, // Vertex Buffer ID
		positionID, //Position ID
		colorID; // Color ID


void Game::initialize()
{
	isRunning = true;
	GLint isCompiled = 0;
	GLint isLinked = 0;

	glewInit();

	/* Vertices counter-clockwise winding */
	vertex[0].coordinate[0] = -0.5f;
	vertex[0].coordinate[1] = -0.5f;
	vertex[0].coordinate[2] = 0.0f;

	vertex[1].coordinate[0] = -0.5f;
	vertex[1].coordinate[1] = 0.5f;
	vertex[1].coordinate[2] = 0.0f;

	vertex[2].coordinate[0] = 0.5f;
	vertex[2].coordinate[1] = 0.5f;
	vertex[2].coordinate[2] = 0.0f;

	vertex[3].coordinate[0] = 0.5f;
	vertex[3].coordinate[1] = 0.5f;
	vertex[3].coordinate[2] = 0.0f;

	vertex[4].coordinate[0] = 0.5f;
	vertex[4].coordinate[1] = -0.5f;
	vertex[4].coordinate[2] = 0.0f;

	vertex[5].coordinate[0] = -0.5f;
	vertex[5].coordinate[1] = -0.5f;
	vertex[5].coordinate[2] = 0.0f;

	vertex[0].color[0] = 0.5f;
	vertex[0].color[1] = 0.0f;
	vertex[0].color[2] = 0.5f;
	vertex[0].color[3] = 1.0f;

	vertex[1].color[0] = 0.5f;
	vertex[1].color[1] = 0.0f;
	vertex[1].color[2] = 0.5f;
	vertex[1].color[3] = 1.0f;

	vertex[2].color[0] = 0.5f;
	vertex[2].color[1] = 0.0f;
	vertex[2].color[2] = 0.5f;
	vertex[2].color[3] = 1.0f;

	vertex[3].color[0] = 0.2f;
	vertex[3].color[1] = 0.0f;
	vertex[3].color[2] = 0.5f;
	vertex[3].color[3] = 1.0f;

	vertex[4].color[0] = 0.0f;
	vertex[4].color[1] = 0.2f;
	vertex[4].color[2] = 0.5f;
	vertex[4].color[3] = 1.0f;

	vertex[5].color[0] = 0.0f;
	vertex[5].color[1] = 0.0f;
	vertex[5].color[2] = 0.5f;
	vertex[5].color[3] = 1.0f;

	/*Index of Poly / Triangle to Draw */
	for (int i = 0; i < VERTEX_NUMBER; i++)
	{
		triangles[i] = i;
	}

	/* Create a new VBO using VBO id */
	glGenBuffers(1, &vbo);

	/* Bind the VBO */
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	/* Upload vertex data to GPU */
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * VERTEX_NUMBER, vertex, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &index);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte) * VERTEX_NUMBER, triangles, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	/* Vertex Shader */
	std::string vsS = readFromFile("VertexShader.txt");
	const char* vs_src = vsS.c_str(); //Vertex Shader 

	DEBUG_MSG("Setting Up Vertex Shader");

	vsid = glCreateShader(GL_VERTEX_SHADER); //Create Shader and set ID
	glShaderSource(vsid, 1, (const GLchar**)&vs_src, NULL); // Set the shaders source
	glCompileShader(vsid); //Check that the shader compiles

	//Check is Shader Compiled
	glGetShaderiv(vsid, GL_COMPILE_STATUS, &isCompiled);

	if (isCompiled == GL_TRUE) {
		DEBUG_MSG("Vertex Shader Compiled");
		isCompiled = GL_FALSE;
	}
	else
	{
		DEBUG_MSG("ERROR: Vertex Shader Compilation Error");
	}

	/* Fragment Shader*/
	std::string fsS = readFromFile("FragmentShader.txt");
	const char* fs_src = fsS.c_str(); 

	DEBUG_MSG("Setting Up Fragment Shader");

	fsid = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fsid, 1, (const GLchar**)&fs_src, NULL);
	glCompileShader(fsid);
	//Check is Shader Compiled
	glGetShaderiv(fsid, GL_COMPILE_STATUS, &isCompiled);

	if (isCompiled == GL_TRUE) {
		DEBUG_MSG("Fragment Shader Compiled");
		isCompiled = GL_FALSE;
	}
	else
	{
		DEBUG_MSG("ERROR: Fragment Shader Compilation Error");
	}

	DEBUG_MSG("Setting Up and Linking Shader");
	progID = glCreateProgram();	//Create program in GPU
	glAttachShader(progID, vsid); //Attach Vertex Shader to Program
	glAttachShader(progID, fsid); //Attach Fragment Shader to Program
	glLinkProgram(progID);

	//Check is Shader Linked
	glGetProgramiv(progID, GL_LINK_STATUS, &isLinked);

	if (isLinked == 1) {
		DEBUG_MSG("Shader Linked");
	}
	else
	{
		DEBUG_MSG("ERROR: Shader Link Error");
	}

	// Use Progam on GPU
	// https://www.opengl.org/sdk/docs/man/html/glUseProgram.xhtml
	glUseProgram(progID);

	// Find variables in the shader
	// https://www.khronos.org/opengles/sdk/docs/man/xhtml/glGetAttribLocation.xml
	positionID = glGetAttribLocation(progID, "sv_position");
	colorID = glGetAttribLocation(progID, "sv_color");
}

void Game::update()
{
#if (DEBUG >= 2)
	DEBUG_MSG("Update up...");
#endif

	//Allowed movement
	if (movementCLock.getElapsedTime() > sf::milliseconds(30))
	{
		movementCLock.restart();

		//center calculation 
		float sumX = 0;
		float sumY = 0;
		float sumZ = 0;
		for (int i = 0; i < VERTEX_NUMBER; i++)
		{
			sumX += vertex[i].coordinate[0];
			sumY += vertex[i].coordinate[1];
			sumZ += vertex[i].coordinate[2];
		}
		db::Vector3 center(sumX / VERTEX_NUMBER, sumY / VERTEX_NUMBER, sumZ / VERTEX_NUMBER);

		//------------ROTATING--------------------------

		// rotation X 
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
		{
			for (int i = 0; i < VERTEX_NUMBER; i++)
			{
				//adapting to vector
				db::Vector3 v(vertex[i].coordinate[0], vertex[i].coordinate[1], vertex[i].coordinate[2]);

				//rotating
				v = v - center;
				v = v * db::Matrix3::rotationX(1);
				v = v + center;

				//reassigning value 
				vertex[i].coordinate[0] = v.x;
				vertex[i].coordinate[1] = v.y;
				vertex[i].coordinate[2] = v.z;
			}
		}


		// rotation Y
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
		{
			for (int i = 0; i < VERTEX_NUMBER; i++)
			{
				//adapting to vector
				db::Vector3 v(vertex[i].coordinate[0], vertex[i].coordinate[1], vertex[i].coordinate[2]);

				//rotating
				v = v - center;
				v = v * db::Matrix3::rotationY(1);
				v = v + center;

				//reassigning value 
				vertex[i].coordinate[0] = v.x;
				vertex[i].coordinate[1] = v.y;
				vertex[i].coordinate[2] = v.z;
			}
		}

		// rotation Z 
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		{
			for (int i = 0; i < VERTEX_NUMBER; i++)
			{
				//adapting to vector
				db::Vector3 v(vertex[i].coordinate[0], vertex[i].coordinate[1], vertex[i].coordinate[2]);

				//rotating
				v = v - center;
				v = v * db::Matrix3::rotationZ(1);
				v = v + center;

				//reassigning value 
				vertex[i].coordinate[0] = v.x;
				vertex[i].coordinate[1] = v.y;
				vertex[i].coordinate[2] = v.z;
			}
		}

		//------------TRANSLATING------------------------

		// Translating right
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			for (int i = 0; i < VERTEX_NUMBER; i++)
			{
				//adapting to vector
				db::Vector3 v(vertex[i].coordinate[0], vertex[i].coordinate[1], 1);

				//translating
				v = v * db::Matrix3::translate(1, 0);

				//reassigning value
				vertex[i].coordinate[0] = v.x;
				vertex[i].coordinate[1] = v.y;
			}
		}

		// Translating left
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			for (int i = 0; i < VERTEX_NUMBER; i++)
			{
				//adapting to vector
				db::Vector3 v(vertex[i].coordinate[0], vertex[i].coordinate[1], 1);

				//translating
				v = v * db::Matrix3::translate(-1, 0);

				//reassigning value
				vertex[i].coordinate[0] = v.x;
				vertex[i].coordinate[1] = v.y;
			}
		}

		// Translating up
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			for (int i = 0; i < VERTEX_NUMBER; i++)
			{
				//adapting to vector
				db::Vector3 v(vertex[i].coordinate[0], vertex[i].coordinate[1], 1);

				//translating
				v = v * db::Matrix3::translate(0, 1);

				//reassigning value
				vertex[i].coordinate[0] = v.x;
				vertex[i].coordinate[1] = v.y;
			}
		}

		// Translating down
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			for (int i = 0; i < VERTEX_NUMBER; i++)
			{
				//adapting to vector
				db::Vector3 v(vertex[i].coordinate[0], vertex[i].coordinate[1], 1);

				//translating
				v = v * db::Matrix3::translate(0, -1);

				//reassigning value
				vertex[i].coordinate[0] = v.x;
				vertex[i].coordinate[1] = v.y;
			}
		}

		// Scalling up
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::U))
		{
			for (int i = 0; i < VERTEX_NUMBER; i++)
			{
				//adapting to vector
				db::Vector3 v(vertex[i].coordinate[0], vertex[i].coordinate[1], vertex[i].coordinate[2]);

				//scalling
				v = v - center;
				v = v * db::Matrix3::scale3D(101);
				v = v + center;

				//reassigning value
				vertex[i].coordinate[0] = v.x;
				vertex[i].coordinate[1] = v.y;
				vertex[i].coordinate[2] = v.z;
			}
		}

		// Scalling Down
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			for (int i = 0; i < VERTEX_NUMBER; i++)
			{
				//adapting to vector
				db::Vector3 v(vertex[i].coordinate[0], vertex[i].coordinate[1], vertex[i].coordinate[2]);

				//scalling
				v = v - center;
				v = v * db::Matrix3::scale3D(99);
				v = v + center;

				//reassigning value
				vertex[i].coordinate[0] = v.x;
				vertex[i].coordinate[1] = v.y;
				vertex[i].coordinate[2] = v.z;
			}
		}

	}

}

void Game::render()
{

#if (DEBUG >= 2)
	DEBUG_MSG("Drawing...");
#endif

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);

	/*	As the data positions will be updated by the this program on the
		CPU bind the updated data to the GPU for drawing	*/
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * VERTEX_NUMBER, vertex, GL_STATIC_DRAW);

	/*	Draw Triangle from VBO	(set where to start from as VBO can contain
		model components that 'are' and 'are not' to be drawn )	*/

	// Set pointers for each parameter
	// https://www.opengl.org/sdk/docs/man4/html/glVertexAttribPointer.xhtml
	glVertexAttribPointer(positionID, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(colorID, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (float*)NULL+3);

	//Enable Arrays
	glEnableVertexAttribArray(positionID);
	glEnableVertexAttribArray(colorID);

	glDrawElements(GL_TRIANGLES, VERTEX_NUMBER, GL_UNSIGNED_BYTE, (char*)NULL + 0);

	window.display();

}

void Game::unload()
{
#if (DEBUG >= 2)
	DEBUG_MSG("Cleaning up...");
#endif
	glDeleteProgram(progID);
	glDeleteBuffers(1, &vbo);
}

