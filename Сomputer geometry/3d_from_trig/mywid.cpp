#include "mywid.h"
#include <QPainter>

mywid::mywid(QWidget *parent) : QWidget(parent)
{

}
void line(Vec2i p0, Vec2i p1, QImage &image, TGAColor color) {
    bool steep = false;
    if (std::abs(p0.x-p1.x)<std::abs(p0.y-p1.y)) {
        std::swap(p0.x, p0.y);
        std::swap(p1.x, p1.y);
        steep = true;
    }
    if (p0.x>p1.x) {
        std::swap(p0, p1);
    }

    for (int x=p0.x; x<=p1.x; x++) {
        float t = (x-p0.x)/(float)(p1.x-p0.x);
        int y = p0.y*(1.-t) + p1.y*t;
        if (steep) {
            image.setPixelColor(y, x, QColor(color.r, color.g, color.b));
        } else {
            image.setPixelColor(x, y, QColor(color.r, color.g, color.b));
        }
    }
}

void triangle(Vec2i t0, Vec2i t1, Vec2i t2, QImage &image, TGAColor color) {
    if (t0.y==t1.y && t0.y==t2.y) return; // i dont care about degenerate triangles
    if (t0.y>t1.y) std::swap(t0, t1);
    if (t0.y>t2.y) std::swap(t0, t2);
    if (t1.y>t2.y) std::swap(t1, t2);
    int total_height = t2.y-t0.y;
    for (int i=0; i<total_height; i++) {
        bool second_half = i>t1.y-t0.y || t1.y==t0.y;
        int segment_height = second_half ? t2.y-t1.y : t1.y-t0.y;
        float alpha = (float)i/total_height;
        float beta  = (float)(i-(second_half ? t1.y-t0.y : 0))/segment_height; // be careful: with above conditions no division by zero here
        Vec2i A = t0 + (t2-t0)*alpha;
        Vec2i B = second_half ? t1 + (t2-t1)*beta : t0 + (t1-t0)*beta;
        if (A.x>B.x) std::swap(A, B);
        for (int j=A.x; j<=B.x; j++) {
            //image.set(j, t0.y+i, color); // attention, due to int casts t0.y+i != A.y
            image.setPixelColor(j, t0.y+i, QColor(0, color.g, 0));
            //image.setPixelColor(j, t0.y+i, QColor(color.r, color.g, color.b));//QColor(x % 255, 100, 255 - y % 255));
        }
    }
}
void mywid::paintEvent(QPaintEvent *event)
{

  QPainter p(this);
  QImage img(1600, 1600, QImage::Format_RGB32);

  //SimpleScene sc(W, H);

  //nado *n;
  Model * model =new Model();
  Vec3f light_dir(0,0,-1);
 //std::cerr<<"alive"<<std::endl;
      for (int i=0; i<model->nfaces(); i++)
      {
          std::vector<int> face = model->face(i);
          Vec2i screen_coords[3];
          Vec3f world_coords[3];
          for (int j=0; j<3; j++)
          {
             // std::cerr<<(model->verts_).size()<<std::endl;
              //std::cerr<<model->faces_[0].size()<<std::endl;
              Vec3f v = model->vert(face[j]);
              //std::cerr<<"alive"<<std::endl;
              screen_coords[j] = Vec2i((v.x+1.)*W/20, (v.y+1.)*H/20);
              world_coords[j]  = v;
          }

          Vec3f n = (world_coords[2]-world_coords[0])^(world_coords[1]-world_coords[0]);

          n.normalize();
          float intensity = n*light_dir;
          if (intensity>0) {
              triangle(screen_coords[0], screen_coords[1], screen_coords[2], img, TGAColor(intensity*255, intensity*255, intensity*255, 255));
          }
      }

  //std::cerr<<"alive"<<std::endl;
  /*
  const float fov= M_PI/3.;
  for(int y = 0; y < H; y++)
    for(int x = 0; x < W; x++)
    {
        float dir_x =  (x + 0.5) -  W/2.;
        float dir_y = -(y + 0.5) + H/2.;    // this flips the image at the same time
        float dir_z = -W/(2.*tan(fov/2.));
       // framebuffer[i+j*width] = cast_ray(vec3{0,0,0}, vec3{dir_x, dir_y, dir_z}.normalize(), spheres, lights);
        Vec3f qw=n->cast_ray(Vec3f{0,0,0}, Vec3f{dir_x, dir_y, dir_z}.normalize(), spheres, lights, duck);
        std::cerr<<"alive"<<std::endl;
        //TColor col = sc.get_pixel(x, y);
       // std::cout<<qw.x<<" "<<qw.y<<" "<<qw.z<<std::endl;
        img.setPixelColor(x, y, QColor(qw.x*170, qw.y*170, qw.z*170));//QColor(x % 255, 100, 255 - y % 255));
        //img.setPixelColor(x, y, QColor(120, 200, 140, 255));
    }*/
  p.translate(W, H);
  p.rotate(180);
 // p.translate(-W/2, -H/2);
  p.drawImage(0, 0, img);
 // p.drawImage();
 // n->render(spheres, lights);

}
