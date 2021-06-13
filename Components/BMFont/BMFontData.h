#ifndef BMFONT_DATA_H
#define BMFONT_DATA_H

/**
 * @brief bmfont_data_t ビットマップフォント一文字ごとの情報
 * 
 */
typedef struct {
    int id;
    int x;
    int y;
    int width;
    int height;
    int xoffset;
    int yoffset;
    int xadvance;
    int page;
    int chnl;
} bmfont_data_t;

#endif