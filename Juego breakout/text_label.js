class TextLabel {
    constructor(position, font, color) {
        this.position = position;
        this.font = font;
        this.color = color;
    }

    draw(ctx, text) {
        ctx.font = this.font;
        ctx.fillStyle = this.color;
        ctx.fillText(text, this.position.x, this.position.y);
    }
}