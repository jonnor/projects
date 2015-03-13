// g++ -o voronoi-3dp voronoi-3dp.cpp `pkg-config --libs --cflags opencv` && ./voronoi-3dp

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

#include <iostream>
#include <fstream>

using namespace cv;
using namespace std;

const int FILLED = -1;
const int LINE_8 = 8;
const int LINE_AA = 16;

static void draw_subdiv_point( Mat& img, Point2f fp, Scalar color )
{
    circle( img, fp, 3, color, FILLED, LINE_8, 0 );
}

static void draw_subdiv( Mat& img, Subdiv2D& subdiv, Scalar delaunay_color )
{
#if 1
    vector<Vec6f> triangleList;
    subdiv.getTriangleList(triangleList);
    vector<Point> pt(3);

    for( size_t i = 0; i < triangleList.size(); i++ )
    {
        Vec6f t = triangleList[i];
        pt[0] = Point(cvRound(t[0]), cvRound(t[1]));
        pt[1] = Point(cvRound(t[2]), cvRound(t[3]));
        pt[2] = Point(cvRound(t[4]), cvRound(t[5]));
        line(img, pt[0], pt[1], delaunay_color, 1, LINE_AA, 0);
        line(img, pt[1], pt[2], delaunay_color, 1, LINE_AA, 0);
        line(img, pt[2], pt[0], delaunay_color, 1, LINE_AA, 0);
    }
#else
    vector<Vec4f> edgeList;
    subdiv.getEdgeList(edgeList);
    for( size_t i = 0; i < edgeList.size(); i++ )
    {
        Vec4f e = edgeList[i];
        Point pt0 = Point(cvRound(e[0]), cvRound(e[1]));
        Point pt1 = Point(cvRound(e[2]), cvRound(e[3]));
        line(img, pt0, pt1, delaunay_color, 1, LINE_AA, 0);
    }
#endif
}

static void locate_point( Mat& img, Subdiv2D& subdiv, Point2f fp, Scalar active_color )
{
    int e0=0, vertex=0;

    cout << "locate: " << fp << "\n";
    subdiv.locate(fp, e0, vertex);

    if( e0 > 0 )
    {
        int e = e0;
        do
        {
            Point2f org, dst;
            if( subdiv.edgeOrg(e, &org) > 0 && subdiv.edgeDst(e, &dst) > 0 )

                line( img, org, dst, active_color, 3, LINE_AA, 0 );

            e = subdiv.getEdge(e, Subdiv2D::NEXT_AROUND_LEFT);
        }
        while( e != e0 );
    }

    // interactive drawing
    draw_subdiv_point( img, fp, active_color );
}


static void paint_voronoi( Mat& img, Subdiv2D& subdiv )
{
    vector<vector<Point2f> > facets;
    vector<Point2f> centers;
    subdiv.getVoronoiFacetList(vector<int>(), facets, centers);

    vector<Point> ifacet;
    vector<vector<Point> > ifacets(1);

    for( size_t i = 0; i < facets.size(); i++ )
    {
        ifacet.resize(facets[i].size());
        for( size_t j = 0; j < facets[i].size(); j++ )
            ifacet[j] = facets[i][j];

        Scalar color(0, 0, 0);

        color[0] = rand() & 255;
        color[1] = rand() & 255;
        color[2] = rand() & 255;

        fillConvexPoly(img, ifacet, color, 8, 0);

        ifacets[0] = ifacet;
        polylines(img, ifacets, true, Scalar(), 1, LINE_AA, 0);
        circle(img, centers[i], 3, Scalar(), FILLED, LINE_AA, 0);
    }
}


std::vector<char> readFile(const char *path) {
    std::ifstream file(path, std::ios::binary);
    file.seekg(0, std::ios::end);
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    // cout << "size" << size;

    std::vector<char> buffer(size);
    if (!file.read(buffer.data(), size))
    {
        exit(2);
    }
    return buffer;
}


void print_vector(vector<string> strs) {
    for (size_t i = 0; i < strs.size(); i++) {
        cout << strs[i] << endl;
    }
}

vector<Point3f>
parse_points(vector<char> file)
{

    vector<Point3f> input_points;
    vector<string> lines;
    boost::split(lines, file, boost::is_any_of("\r\n"));

    // print_vector(lines);

    for (int line_no=0; line_no < lines.size(); line_no++) {
        const std::string line = lines[line_no];
        // cout << line << "\n";
        vector<string> tokens;
        boost::split(tokens, line, boost::is_any_of(","));
        // cout << "tokens: " << tokens.size() << "\n";
        if (tokens.size() == 3) {
            float a[3] = {0, 0, 0};
            for (int i=0; i<2; i++) {
                std::string tok = tokens[i];
                boost::trim_if(tok, boost::is_any_of(" {}"));
//                cout << "token: " << tok << "\n";
                a[i] = boost::lexical_cast<float>(tok);
//                cout << "out: " << a[i] << "\n";
            }
            Point3f p(a[0], a[1], a[2]);
            // cout << "adding point" << p;
            input_points.push_back(p);
        }
    }

    return input_points;
}

// XXX: replace with something stock
Rect
calculate_xy_bounds(vector<Point3f> points)
{
    float x0 = points.at(0).x;
    float y0 = points.at(0).y;
    float x1 = x0;
    float y1 = y0;
    for (int i=0; i<points.size(); i++) {
        Point3f p = points[i];
        if (p.x < x0) {
            x0 = p.x;
        }
        if (p.x > x1) {
            x1 = p.x;
        }
        if (p.y < y0) {
            y0 = p.y;
        }
        if (p.y > y1) {
            y1 = p.y;
        }
    }

    return Rect(x0, y0, x1-x0, y1-y0);
}

int main( int, char** )
{
    // TODO: calculate bounding box of model
    Scalar active_facet_color(0, 0, 255), delaunay_color(255,255,255);
    Rect rect(0, 0, 1000, 1000);

    Subdiv2D subdiv(rect);
    Mat img(rect.size(), CV_8UC3);

    img = Scalar::all(0);
    string win = "Delaunay Demo";
    imshow(win, img);

    // Read in from file
    vector<char> file = readFile("voronoi-input-test1.txt"); // TODO: pass as stdin
    vector<Point3f> input_points = parse_points(file);
    // Rect model_bounds = calculate_xy_bounds(input_points);
    Rect bounds(-40, -12, 40*2, 12*2); // TODO: specify from outside.
    // FIXME: code to do mesh intersect? OR let Cura handle it

    cout << "number of points " << input_points.size() << "\n";
    cout << "bounding box" << bounds << "\n";

    // TODO: autocenter/scale
    Point2f translate(500, 500);
//    Point2f scale(6.f, 6.f);
    Point2f scale(rect.width/bounds.width, rect.height/bounds.height);

    for( int i = 0; i < input_points.size(); i++ )
    {

        // Use inputs instead
        const Point3f ip = input_points.at(i);
        Point2f fp = Point2f(ip.x, ip.y);

        // Clip to bounds
        if (fp.x < bounds.x || fp.y < bounds.y ||
            fp.x > (bounds.x+bounds.width) || fp.y > (bounds.y+bounds.height)) {
            continue;
        }

        fp.x *= scale.x;
        fp.y *= scale.y;
        fp = fp+translate;
        // cout << "i: " << i << " " << fp.x << ", " << fp.y << "\n";

        locate_point( img, subdiv, fp, active_facet_color );

        subdiv.insert(fp);
    }

    img = Scalar::all(0);
    paint_voronoi( img, subdiv );
    imshow( win, img );

    waitKey(0);

    return 0;
}


