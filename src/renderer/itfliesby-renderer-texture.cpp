#pragma once

#include "itfliesby-renderer.hpp"

internal ItfliesbyRendererTextureStore
itfliesby_renderer_texture_store_init() {

    ItfliesbyRendererTextureStore textures = {0};

    //character textures
    textures.sprites_characters.gl_texture_unit = GL_TEXTURE0;

    return(textures);
}

external void
itfliesby_renderer_texture_sprite_character_load(
    ItfliesbyRenderer*                          renderer,
    ItfliesbyRendererTextureSpriteCharacterType sprite_character_type,
    u32                                         sprite_character_data_width_bytes,
    u32                                         sprite_character_data_height_bytes,
    memory                                      sprite_character_data) {

    ItfliesbyRendererTextureStore*               texture_store                         = &renderer->textures;
    ItfliesbyRendererGlTextureSpritesCharacters* character_sprites                     = &texture_store->sprites_characters;
    GLuint*                                      character_sprites_gl_texture_id_array = character_sprites->gl_texture_id_array;

    //get the texture id
    GLuint character_sprite_gl_texture_id = character_sprites_gl_texture_id_array[sprite_character_type];

    //if we have an existing texture, delete it
    if (character_sprite_gl_texture_id != 0) {
        glDeleteTextures(1,&character_sprite_gl_texture_id);
    }

    //generate the texture
    glGenTextures(1, &character_sprite_gl_texture_id);
    glBindTexture(GL_TEXTURE_2D,character_sprite_gl_texture_id);
    glTexImage2D(
        GL_TEXTURE_2D, 
        0,
        GL_RGBA,
        sprite_character_data_width_bytes,
        sprite_character_data_height_bytes,
        0,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        sprite_character_data);

    //write the texture id back
    character_sprites_gl_texture_id_array[sprite_character_type] = character_sprite_gl_texture_id;
}