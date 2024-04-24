//
// Created by Alienso on 14.4.2023..
//

#ifndef GRASSTERRAIN_FRAMEBUFFER_H
#define GRASSTERRAIN_FRAMEBUFFER_H

enum FrameBufferType{
    FRAME_BUFFER_REGULAR,
    FRAME_BUFFER_SHADOW
};

class FrameBuffer {
public:
    explicit FrameBuffer(FrameBufferType type = FRAME_BUFFER_REGULAR);
    ~FrameBuffer();
    void bind() const;
    void unbind() const;
    void bindTexture() const;

    [[nodiscard]] unsigned int getTextureId() const{
        return renderedTexture;
    }

private:
    unsigned int rendererID;
    unsigned int renderedTexture;

    void createTexture();
    void createShadowTexture();
};


#endif //GRASSTERRAIN_FRAMEBUFFER_H
