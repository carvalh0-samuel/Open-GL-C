#include <GL/glut.h>

float posX = 0.0f; // Posição inicial do quadrado

// Função que desenha o quadrado na posição atual
void Desenha(void) {
    glClear(GL_COLOR_BUFFER_BIT); // Limpa a janela

    // Quadrado de cor vermelha
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(posX + 100, 150);
        glVertex2f(posX + 100, 100);

        // Mudança para cor azul
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex2f(posX + 150, 100);
        glVertex2f(posX + 150, 150);
    glEnd();

    glFlush(); // Executa os comandos OpenGL
}

// Função que atualiza a posição do quadrado
void Atualiza(int valor) {
    posX += 1.0f; // Incrementa a posição do quadrado no eixo X

    // Se o quadrado ultrapassar a borda direita, volta para a esquerda
    if (posX > 250) {
        posX = -150.0f;
    }

    glutPostRedisplay(); // Solicita a re-renderização da cena
    glutTimerFunc(16, Atualiza, 0); // Chama novamente após 16 milissegundos (~60 FPS)
}

void Inicializa(void) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Cor de fundo preta
}

void MudaTamanhoJanela(GLsizei w, GLsizei h) {
    if (h == 0) h = 1; // Evita divisão por zero

    glViewport(0, 0, w, h); // Define a área de visualização

    glMatrixMode(GL_PROJECTION); // Define a matriz de projeção
    glLoadIdentity(); // Reseta a matriz de projeção

    if (w <= h)
        gluOrtho2D(0.0f, 250.0f, 0.0f, 250.0f * h / w); // Ajuste para manter a proporção
    else
        gluOrtho2D(0.0f, 250.0f * w / h, 0.0f, 250.0f); // Ajuste para manter a proporção
}

int main(int argc, char** argv) {
    glutInit(&argc, argv); // Inicializa o GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Modo de exibição
    glutInitWindowSize(500, 350); // Tamanho da janela
    glutInitWindowPosition(50, 30); // Posição da janela
    glutCreateWindow("Quadrado em Movimento"); // Cria a janela com título

    glutDisplayFunc(Desenha); // Registra a função de exibição
    glutReshapeFunc(MudaTamanhoJanela); // Registra a função de redimensionamento

    Inicializa(); // Configurações iniciais

    // Configura a função de timer para atualizar o quadrado
    glutTimerFunc(16, Atualiza, 0); // Atualiza a cada 16 milissegundos (~60 FPS)

    glutMainLoop(); // Inicia o loop do GLUT

    return 0;
}
