#include "common-core.h"
#include "common-ext.h"
#include <stdlib.h>

static void spin(BiContext* context,BiNode* node)
{
    bi_node_set_angle(node, node->angle + 0.01);
}

static void world_create(BiContext* context)
{
    bi_set_color(context->color,0xff,32,128,0xff);

    //
    // face sprite layer
    //
    // sprite
    BiNode *sprite = make_sprite("assets/face01.png");
    sprite->scale_x = sprite->scale_y = 2.0;
    bi_node_set_position(sprite,context->w/2,context->h/2);
    bi_set_color(sprite->color, 0xff, 0xff, 0xff, 0xff);
    // shadow
    BiNode *shadow = malloc(sizeof(BiNode));
    bi_node_init(shadow);
    bi_node_set_size(shadow,context->w,context->h);
    bi_set_color(shadow->color, 0, 0, 0, 128);
    // root
    BiNode *root = malloc(sizeof(BiNode));
    bi_node_init(root);
    bi_node_add_node(root,sprite);
    bi_node_add_node(root,shadow);
    // layer
    BiLayer *layer = malloc(sizeof(BiLayer));
    bi_layer_init(layer);
    layer->root = root;
    layer->textures[0] = sprite->texture_mapping->texture;

    bi_add_layer(context,layer);

    //
    // spotlight layer
    //

    // sprite
    BiNode *spotlight = make_sprite("assets/circle256.png");
    bi_node_set_position(spotlight,context->w/2,context->h/2);
    bi_set_color(spotlight->color, 0xff, 0xff, 0xff, 0xff);
    // spin sprite!
    bi_node_set_on_update(spotlight,spin);
    // spotlight layer
    BiLayer *spotlight_layer = malloc(sizeof(BiLayer));
    bi_layer_init(spotlight_layer);
    spotlight_layer->root = spotlight;
    bi_add_layer(context,spotlight_layer);
    // spotlight blend setting
    spotlight_layer->blend_src = GL_DST_COLOR;
    spotlight_layer->blend_dst = GL_ONE;
    // textures
    spotlight_layer->textures[0] = spotlight->texture_mapping->texture;

    //
    // fps layer
    //
    BiFontAtlas *font = load_font();
    add_fps_layer(context,font);
}

int main(int argc,char* argv[])
{
    print_version();
    BiContext* context = malloc(sizeof(BiContext));
    bi_init_context(context, 480, 320, 0, false, __FILE__);
    world_create(context);
    bi_start_run_loop(context);
    return 0;
}
