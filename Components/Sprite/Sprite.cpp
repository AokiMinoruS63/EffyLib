#include "Sprite.h"
#include "SpriteTimelineItem.h"
#include "../Physicus/PhysicusWorld/PhysicusWorld.h"

// TODO: グローバル座標とローカル座標を作る
// ループフラグも作る。カウント変数も作る

Sprite::Sprite() {
	this->common_ = defaultCommon;
	parametersInit(&local_);
	parametersInit(&global_);
	timelineInit(&local_timeline_);
	timelineInit(&global_timeline_);
}

Sprite::~Sprite() {

}
/*
static sprite_common_t Sprite::defaultCommon() {
	sprite_common_t common;
	common.imgHandle = -1;
	common.su = 0.0;
	common.sv = 0.0;
	common.gu = 1.0;
	common.gv = 1.0;
	common.offsetU = 0.5;
	common.offsetV = 0.5;
	common.endFrame = 0;
	common.frame = 0;
	common.loop = true;
	return common;
}*/

void Sprite::timelineInit(sprite_timeline_t *line) {
	const sprite_timeline_item_t zero = {/* frame */0, /* num */0.0,   /* start_type */0, /* end_type */0};
	const sprite_timeline_item_t one =  {/* frame */0, /* num */1.0,   /* start_type */0, /* end_type */0};
	const sprite_timeline_item_t max =  {/* frame */0, /* num */255.0, /* start_type */0, /* end_type */0};
	const sprite_timeline_item_t half = {/* frame */0, /* num */0.5,   /* start_type */0, /* end_type */0};
	line->x.push_back(zero);
	line->y.push_back(zero);
	line->scale.push_back(one);
	line->color_r.push_back(max);
	line->color_g.push_back(max);
	line->color_b.push_back(max);
	line->color_a.push_back(max);
	line->angle.push_back(zero);
	line->rotate_u.push_back(half);
	line->rotate_v.push_back(half);
	line->before_scale_x.push_back(one);
	line->before_scale_y.push_back(one);
	line->after_scale_x.push_back(one);
	line->after_scale_y.push_back(one);
}

void Sprite::parametersInit(sprite_parameters_t *parameter) {
	const float zero = 0.0;
	const float one = 1.0;
	const float max = 255.0;
	const float half = 0.5;
	parameter->x = zero;
	parameter->y = zero;
	parameter->scale = one;
	parameter->color_r = max;
	parameter->color_g = max;
	parameter->color_b = max;
	parameter->color_a = max;
	parameter->angle = zero;
	parameter->rotate_u = half;
	parameter->rotate_v = half;
	parameter->before_scale_x = one;
	parameter->before_scale_y = one;
	parameter->after_scale_x = one;
	parameter->after_scale_y = one;
}

void Sprite::calc() {
	// TODO: 計算処理を行う。ベジェ曲線を使用した補完を行う
}
/*
void Sprite::getPos(float *x, float *y) {
    *x = this->x;
    *y = this->y;
}
float Sprite::getScale() {
    return scale;
}
void Sprite::getColor(float *r, float *g, float *b, float *a) {
    *r = this->colorR;
    *g = this->colorG;
    *b = this->colorB;
    *a = this->colorA;
}

float Sprite::getAngle() {
    return this->angle;
}

void Sprite::getRotateUV(float *u, float *v) {
    *u = this->rotateU;
    *v = this->rotateV;
}

void Sprite::getBeforeScale(float *beforeScaleX, float *beforeScaleY) {
    *beforeScaleX = this->beforeScaleX;
    *beforeScaleY = this->beforeScaleY;
}

void Sprite::getAfterScale(float *afterScaleX, float *afterScaleY) {
    *afterScaleX = this->afterScaleX;
    *afterScaleY = this->afterScaleY;
}

void Sprite::setPos(float x, float y) {
    this->x = x;
    this->y = y;
}

void Sprite::setScale(float scale) {
    this->scale = scale;
}

void Sprite::setColor(float r, float g, float b, float a) {
    this->colorR = r;
    this->colorG = g;
    this->colorB = b;
    this->colorA = a;
}

void Sprite::setAngle(float angle) {
    this->angle = angle;
}

void Sprite::setRotateUV(float u, float v) {
    this->rotateU = u;
    this->rotateV = v;
}

void Sprite::setBeforeScale(float beforeScaleX, float beforeScaleY) {
    this->beforeScaleX = beforeScaleX;
    this->beforeScaleY = beforeScaleY;
}

void Sprite::setAfterScale(float afterScaleX, float afterScaleY) {
    this->afterScaleX = afterScaleX;
    this->afterScaleY = afterScaleY;
}
*/