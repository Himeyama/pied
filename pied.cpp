#include <iostream>
#include <opencv2/opencv.hpp>

#define print(x) cout << x << ends
#define puts(x) cout << x << endl

using namespace cv;
using namespace std;

class ImgErrDiff{
    public:
    Mat img1;
    Mat img2;
    int row_size;
    int column_size;
    Mat color_palette;

    // ユークリッド距離
    double euqlid(const Scalar color1, const Scalar color2){
        return 
        sqrt((color2[0] - color1[0]) * (color2[0] - color1[0]) 
        + (color2[1] - color1[1]) * (color2[1] - color1[1]) 
        + (color2[2] - color1[2]) * (color2[2] - color1[2]));
    }

    // ユークリッド距離が最小の色を選択
    Vec3b select_color(const Scalar color){
        const int palette_size = this -> color_palette.cols;

        double min = euqlid((Scalar)this -> color_palette.at<Vec3b>(0, 0), color);
        int index = 0;
        for(int i=1; i<palette_size; i++){
            double tmp = euqlid((Scalar)this -> color_palette.at<Vec3b>(0, i), color);
            if(tmp < min){
                min = tmp;
                index = i;
            }
        }
        return this -> color_palette.at<Vec3b>(0, index);
    }

    //処理開始
    void run(){
        this -> row_size = img1.rows;
        this -> column_size = img1.cols;
        this -> img2 = Mat(this -> row_size, this -> column_size, CV_8UC3);
        for(int i=0; i< this -> row_size; i++){
            for(int j=0; j < this -> column_size; j++){
                Vec3b tmp = select_color((Scalar)this -> img1.at<Vec3b>(i, j));
                Vec3b diff = this -> img1.at<Vec3b>(i, j) - tmp;
                this->img2.at<Vec3b>(i, j) = tmp;
                if (j < this -> column_size - 2)
                    this -> img1.at<Vec3b>(i, j + 1) += diff * 0.4375;
                if (i < this -> row_size - 2 && j < this -> column_size - 2)
                    this -> img1.at<Vec3b>(i + 1, j + 1) += diff * 0.0625;
                if (i < this -> row_size - 2)
                    this -> img1.at<Vec3b>(i + 1, j) += diff * 0.3125;
                if (i < this -> row_size - 2 && j > 0)
                    this -> img1.at<Vec3b>(i + 1, j - 1) += diff * 0.1875;
            }
            printf("\e[G%d/%d (%.1f%%)", i+1, this -> row_size, (i+1)*100.0/this -> row_size);
        }
        puts("");
    }

    void open(const String filename){
        this -> img1 = imread(filename);
    }

    void setColorPalette(const String filename){
        this -> color_palette = imread(filename);
    }

    void save(const String filename){
        imwrite(filename, this -> img2);
    }
};

int main(int argc, const char* argv[]){
    if(argc != 4){
        print("Usage: ");
        print(argv[0]);
        puts(" InputImage OutputImage PaletteImage");
        return 0;
    }
    
    ImgErrDiff image_error_diff;
    image_error_diff.setColorPalette(argv[3]);
    image_error_diff.open(argv[1]);
    image_error_diff.run();
    image_error_diff.save(argv[2]);
    
    return 0;
}