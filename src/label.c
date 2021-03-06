#include "common-core.h"
#include "common-ext.h"

static BiFontAtlas* load_font_atlas(const char* name, BiTexture *font_texture)
{
    BiFontAtlas *font = malloc(sizeof(BiFontAtlas));
    bi_load_font_layout_from_file(name,font);
    font->texture = font_texture;
    return font;
}

void world_create(BiContext* context)
{
    // layer
    BiLayer *layer = malloc(sizeof(BiLayer));
    bi_layer_init(layer);
    bi_add_layer(context,layer);

    // root node
    BiNode* root = malloc(sizeof(BiNode));
    bi_node_init(root);
    layer->root = root;

    // font
    BiTexture *font_texture = malloc(sizeof(BiTexture));
    bi_texture_init_with_filename(font_texture,"assets/mixed.png",false);
    BiFontAtlas *fonts[4];
    fonts[0] = load_font_atlas("assets/small.dat", font_texture),
    fonts[1] = load_font_atlas("assets/small-bold.dat", font_texture);
    fonts[2] = load_font_atlas("assets/large.dat", font_texture);
    fonts[3] = load_font_atlas("assets/large-bold.dat", font_texture);
    layer->textures[0] = font_texture;

    // labels
    int offset_x = 20;
    int offset_y = 20;
    for(int i=0; i<4; i++){
      BiNode* label = malloc(sizeof(BiNode));
      bi_node_init(label);
      bi_set_color(label->color,32,32,32,0xff);
      bi_node_set_position( label, offset_x, offset_y+i*20 );
      bi_update_label(label, "The quick brown fox jumps over the lazy dog", fonts[i], 0xFF,0xFF,0xFF,0xFF);
      bi_node_add_node(root,label);
    }
    for(int i=0; i<4; i++){
      BiNode* label = malloc(sizeof(BiNode));
      bi_node_init(label);
      bi_set_color(label->color,32,32,32,0xff);
      bi_node_set_position( label, offset_x, offset_y+(4+i)*20 );
      bi_update_label(label, "いろはにほへと　ちりぬるを　わかよたれそ　つねならむ", fonts[i], 0xFF,0xFF,0xFF,0xFF);
      bi_node_add_node(root,label);
    }
    for(int i=0; i<4; i++){
      BiNode* label = malloc(sizeof(BiNode));
      bi_node_init(label);
      bi_set_color(label->color,32,32,32,0xff);
      bi_node_set_position( label, offset_x, offset_y+(8+i)*20 );
      bi_update_label(label, "カタカナと、Alphabetと、ひらがな。", fonts[i], 0xFF,0xFF,0xFF,0xFF);
      bi_node_add_node(root,label);
    }

    // fps layer
    add_fps_layer(context,fonts[0]);
}

int main(int argc, char* argv[])
{
    print_version();
    BiContext* context = malloc(sizeof(BiContext));
    bi_init_context(context, 480, 320, 0, true, __FILE__);
    world_create(context);
    bi_start_run_loop(context);
    return 0;
}
