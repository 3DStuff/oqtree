#ifdef DEBUG
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace cv;


template <typename payload_t>
void draw_quad_tree(const tree<quad::boundary, payload_t> &t) {
    /// Windows names
    char tree_window[] = "Drawing 1: Atom";
    float offs = 16;
    float scale_f = 1024.f / (glm::max(t._boundary._dim.x, t._boundary._dim.y)*2.f + 2*offs);
    
    int w = t._boundary._dim.x*2 * scale_f + 2*offs;
    int h = t._boundary._dim.y*2 * scale_f + 2*offs;

    /// Create black empty images
    Mat tree_image = Mat( h, w, CV_8UC4, Scalar(255,255,255,0) );    
    std::vector<test::draw_data> dta;
    
    t.recursive_get_tree(dta);

    for(auto e : dta) {
        auto f = e.rect.low*scale_f+offs;
        auto s = e.rect.high*scale_f+offs;
        Point p1(f.x, f.y);
        Point p2(s.x, s.y);
        
        int pos = rand() % 3;
        int pos2 = rand() % 3;
        
        Scalar color( 0, 0, 0 );
        Scalar lighter( 32, 32, 32 );
        color[pos] = 196;
        color[pos2] = 96;

        // draw rectangle
        rectangle(
            tree_image,
            p1,
            p2,
            color+lighter,
            CV_FILLED
        );
    }
    
    imshow( tree_window, tree_image );
    waitKey( 0 );
}
#endif
