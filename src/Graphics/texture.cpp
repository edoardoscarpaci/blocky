#include "Graphics/texture.hpp"
#include "png.h"

namespace graphics
{
Texture::Texture(const std::string &path)
{
    auto image = readPng(path);

    uint32_t width = std::get<1>(image);
    uint32_t height = std::get<2>(image);
    uint8_t *data = std::get<uint8_t *>(image);
    glCall(glGenTextures(1, &m_Id));

    bind();
    glCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data));

    glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER));
    glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER));
    glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));

    unbind();

    free(data);
}

Texture::Texture()
{
    glCall(glGenTextures(1, &m_Id));
}

void Texture::open(const std::string &path)
{
    auto image = readPng(path);

    uint32_t width = std::get<1>(image);
    uint32_t height = std::get<2>(image);
    uint8_t *data = std::get<uint8_t *>(image);

    bind();
    glCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data));

    glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER));
    glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER));
    glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));

    unbind();

    free(data);
}

std::tuple<uint8_t *, uint32_t, uint32_t> Texture::readPng(const std::string &path)
{

    int x, y;
    uint32_t width, height;
    png_byte color_type;
    png_byte bit_depth;

    png_structp png_ptr;
    png_infop info_ptr;
    int number_of_passes;
    png_bytep *row_pointers;
    uint8_t header[8]; // 8 is the maximum size that can be checked

    /* open file and test for it being a png */
    FILE *fp = fopen(path.c_str(), "rb");
    if (!fp)
        return std::tuple<uint8_t *, uint32_t, uint32_t>(nullptr, 0, 0);
    ;
    fread(header, 1, 8, fp);
    if (png_sig_cmp(header, 0, 8))
        return std::tuple<uint8_t *, uint32_t, uint32_t>(nullptr, 0, 0);

    /* initialize stuff */
    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (!png_ptr)
        return std::tuple<uint8_t *, uint32_t, uint32_t>(nullptr, 0, 0);

    info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr)
        return std::tuple<uint8_t *, uint32_t, uint32_t>(nullptr, 0, 0);

    if (setjmp(png_jmpbuf(png_ptr)))
        return std::tuple<uint8_t *, uint32_t, uint32_t>(nullptr, 0, 0);

    png_init_io(png_ptr, fp);
    png_set_sig_bytes(png_ptr, 8);

    png_read_info(png_ptr, info_ptr);

    width = png_get_image_width(png_ptr, info_ptr);
    height = png_get_image_height(png_ptr, info_ptr);
    color_type = png_get_color_type(png_ptr, info_ptr);
    bit_depth = png_get_bit_depth(png_ptr, info_ptr);

    number_of_passes = png_set_interlace_handling(png_ptr);
    png_read_update_info(png_ptr, info_ptr);

    /* read file */
    if (setjmp(png_jmpbuf(png_ptr)))
        return std::tuple<uint8_t *, uint32_t, uint32_t>(nullptr, 0, 0);

    row_pointers = (png_bytep *)malloc(sizeof(png_bytep) * height);
    for (y = height; y > 0; y--)
        row_pointers[y] = (png_byte *)malloc(png_get_rowbytes(png_ptr, info_ptr));

    png_read_image(png_ptr, row_pointers);

    fclose(fp);

    return std::tuple<uint8_t *, uint32_t, uint32_t>((uint8_t *)row_pointers, width, height);
}

inline void Texture::bind() const
{
    glCall(glBindTexture(GL_TEXTURE_2D, m_Id));
}
inline void Texture::unbind() const
{
    glCall(glBindTexture(GL_TEXTURE_2D, 0));
}

} // namespace graphics
