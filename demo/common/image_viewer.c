#ifndef IMAGE_VIEWER_IMAGE_FILE
#define IMAGE_VIEWER_IMAGE_FILE "../common/image_viewer/image.bmp"
#endif

struct image_viewer {
    nk_bool initialized;
    void (*freeimage)(struct nk_context*, struct nk_image);
    struct nk_context* ctx;
    struct nk_image image;
};

static struct image_viewer imageViewer;

static void
image_viewer(struct nk_context* ctx, struct nk_image (*loadimage)(struct nk_context*, const char*), void (*freeimage)(struct nk_context*, struct nk_image))
{
    if (!imageViewer.initialized) {
        imageViewer.image = loadimage(ctx, IMAGE_VIEWER_IMAGE_FILE);
        imageViewer.freeimage = freeimage;
        imageViewer.initialized = nk_true;
    }

    if (imageViewer.image.handle.ptr == NULL) {
        return;
    }

    if (nk_begin(ctx, "Image Viewer", nk_rect(0, 0, 400, 300),
        NK_WINDOW_BORDER|NK_WINDOW_SCALABLE|NK_WINDOW_MOVABLE|NK_WINDOW_CLOSABLE))
    {
        nk_layout_row_dynamic(ctx, nk_window_get_height(ctx), 1);
        nk_image(ctx, imageViewer.image);

        nk_end(ctx);
    }
}

static void
image_viewer_free() {
    if (imageViewer.initialized && imageViewer.freeimage != NULL) {
        imageViewer.freeimage(imageViewer.ctx, imageViewer.image);
    }
}
