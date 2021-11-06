#include "Cylindre.h"

Cylindre::Cylindre()
{
    this->nombrePoints = 30;
    this->hauteur = 0.5;
    this->rayon = 0.5;
    this->pCylindre = new Point[2*nombrePoints];
}

Cylindre::~Cylindre()
{
   delete[] pCylindre;
}

Cylindre::Cylindre(int newNombrePoint, double newRayon, double newHauteur){
    this->nombrePoints = newNombrePoint;
    this->hauteur = newHauteur;
    this->rayon = newRayon;
    this->pCylindre = new Point[2*nombrePoints];
}

void Cylindre::drawPoint(){
    for (int i = 0; i < this->nombrePoints; i++){
        double theta = (double) (2.0*i*M_PI/this->nombrePoints);
        this->pCylindre[i] = {this->rayon * cos(theta), this->rayon * sin(theta), this->hauteur/2.0};
        this->pCylindre[i+this->nombrePoints] = {this->rayon * cos(theta), this->rayon * sin(theta), -this->hauteur/2.0};
    }
}

void Cylindre::ColorCylindre(float red, float green, float blue){
    for (int i = 0; i < this->nombrePoints; i++){
        glBegin(GL_POLYGON);
        glColor3f(1.0,0.0,0.0);  glVertex3f(this->pCylindre[i].getX(), this->pCylindre[i].getY(), this->pCylindre[i].getZ());
        glColor3f(0.0,1.0,0.0);  glVertex3f(this->pCylindre[(i+1)%this->nombrePoints].getX(), this->pCylindre[(i+1)%this->nombrePoints].getY(), this->pCylindre[(i+1)%this->nombrePoints].getZ());
        glColor3f(0.0,0.0,1.0);  glVertex3f(this->pCylindre[(i+1)%this->nombrePoints+this->nombrePoints].getX(), this->pCylindre[(i+1)%this->nombrePoints+this->nombrePoints].getY(), this->pCylindre[(i+1)%this->nombrePoints+this->nombrePoints].getZ());
        glColor3f(1.0,0.0,1.0);  glVertex3f(this->pCylindre[i+this->nombrePoints].getX(), this->pCylindre[i+this->nombrePoints].getY(), this->pCylindre[i+this->nombrePoints].getZ());
        glEnd();
    }

    glBegin(GL_POLYGON);
        for(int j=0; j<nombrePoints ; j++){
            glColor3f(1.0,0.0,0.0);  glVertex3f(this->pCylindre[j].getX(), this->pCylindre[j].getY(), this->pCylindre[j].getZ());
        }
    glEnd();
    glBegin(GL_POLYGON);
        for(int k=nombrePoints; k<2*nombrePoints ; k++){
            glColor3f(0.0,1.0,0.0);  glVertex3f(this->pCylindre[k].getX(), this->pCylindre[k].getY(), this->pCylindre[k].getZ());
        }
    glEnd();
}

void Cylindre::appliTexture(char* fichier, int l, int h){

    unsigned char img[l*h*3];
    texture = img;
    struct jpeg_decompress_struct cinfo;
  struct jpeg_error_mgr jerr;
  FILE *file;
  unsigned char* ligne;

  cinfo.err = jpeg_std_error(&jerr);
  jpeg_create_decompress(&cinfo);
#ifdef __WIN32
  if (fopen_s(&file,fichier,"rb") != 0)
    {
      fprintf(stderr,"Erreur : impossible d'ouvrir le fichier texture.jpg\n");
      exit(1);
    }
#elif __GNUC__
  if ((file = fopen(fichier,"rb")) == 0)
    {
      fprintf(stderr,"Erreur : impossible d'ouvrir le fichier texture.jpg\n");
      exit(1);
    }
#endif
        //glVertex2f(0,1);
        //glTexCoord2f(0,1);
  jpeg_stdio_src(&cinfo, file);
  jpeg_read_header(&cinfo, TRUE);

  if ((cinfo.image_width!=l)||(cinfo.image_height!=h)) {
    fprintf(stdout,"Erreur : l'image doit etre de taille %dx%d\n", l, h);
    exit(1);
  }

  if (cinfo.jpeg_color_space==JCS_GRAYSCALE) {
    fprintf(stdout,"Erreur : l'image doit etre de type RGB\n");
    exit(1);
  }

  jpeg_start_decompress(&cinfo);
  ligne=texture;
  while (cinfo.output_scanline<cinfo.output_height)
    {
      ligne=texture+3*l*cinfo.output_scanline;
      jpeg_read_scanlines(&cinfo,&ligne,1);
    }
  jpeg_finish_decompress(&cinfo);
  jpeg_destroy_decompress(&cinfo);

  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, l, h, 0, GL_RGB, GL_UNSIGNED_BYTE, texture);
    glEnable(GL_TEXTURE_2D);

    for (int i = 0; i < this->nombrePoints; i++){
        glBegin(GL_POLYGON);
        glTexCoord2f(0.0,0.0);   glVertex3f(this->pCylindre[i].getX(), this->pCylindre[i].getY(), this->pCylindre[i].getZ());
        glTexCoord2f(0.0,1.0);   glVertex3f(this->pCylindre[(i+1)%this->nombrePoints].getX(), this->pCylindre[(i+1)%this->nombrePoints].getY(), this->pCylindre[(i+1)%this->nombrePoints].getZ());
        glTexCoord2f(1.0,1.0);   glVertex3f(this->pCylindre[(i+1)%this->nombrePoints+this->nombrePoints].getX(), this->pCylindre[(i+1)%this->nombrePoints+this->nombrePoints].getY(), this->pCylindre[(i+1)%this->nombrePoints+this->nombrePoints].getZ());
        glTexCoord2f(1.0,0.0);   glVertex3f(this->pCylindre[i+this->nombrePoints].getX(), this->pCylindre[i+this->nombrePoints].getY(), this->pCylindre[i+this->nombrePoints].getZ());
        glEnd();
    }
    glBegin(GL_POLYGON);
    for(int i=0 ; i<this->nombrePoints ; i++){
        glTexCoord2f(0.0,0.0);   glVertex3f(this->pCylindre[i].getX(), this->pCylindre[i].getY(), this->pCylindre[i].getZ());
    }
    glEnd();
    glBegin(GL_POLYGON);
    for(int i=nombrePoints ; i<2*nombrePoints ; i++){
        glTexCoord2f(0.0,0.0);   glVertex3f(this->pCylindre[i].getX(), this->pCylindre[i].getY(), this->pCylindre[i].getZ());
    }
    glEnd();
}

unsigned char* Cylindre::getTexture(){
    return this->texture;
}
