int main(int argc, char* argv[])
    {
        glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
        glutInitWindowSize(800, 600);
        glutInitWindowPosition(300,50);
    glutCreateWindow("GLRect");

glClearColor(1.0f, 0.0f, 0.0f, 1.0f);   

    glutDisplayFunc(RenderScene);
        glutReshapeFunc(ChangeSize);
    glutMainLoop();

    //system("pause");
glClearColor(0.0f, 1.0f, 0.0f, 1.0f);  

        return 0;
    }