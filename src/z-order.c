#include "common-core.h"

static void world_create(BiContext* context)
{
    bi_set_color(context->color,0x33,0x33,0x33,0xff);

    // root node
    BiNode* root = malloc(sizeof(BiNode));
    bi_node_init(root);

    // texture node
    BiNode* face_a = make_sprite("assets/face01.png");
    BiNode* face_b = make_sprite("assets/face01.png");
    bi_set_color( face_a->color, 0, 0xFF, 0, 0xFF); // Green
    bi_set_color( face_b->color, 0, 0, 0xFF, 0xFF); // Blue
    bi_node_set_position(face_a,context->w/2,context->h/2);
    bi_node_set_position(face_b,context->w/2 + 50,context->h/2 + 50);

    bi_node_add_node(root,face_a); // Green
    bi_node_add_node(root,face_b); // Blue

    bi_node_set_z(face_a,1); // Green move to top

    // layer
    BiLayer *layer = malloc(sizeof(BiLayer));
    bi_layer_init(layer);
    bi_add_layer(context,layer);
    layer->root = root;
    layer->textures[0] = face_a->texture_mapping->texture;
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
