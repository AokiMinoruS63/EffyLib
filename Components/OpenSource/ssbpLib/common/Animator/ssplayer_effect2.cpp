
#include <stdio.h>
#include <cstdlib>

#include "../Loader/ssloader.h"

#include "ssplayer_effect2.h"
#include "ssplayer_macro.h"
#include "ssplayer_matrix.h"
#include "ssplayer_effectfunction.h"

#include "../../SS5PlayerPlatform.h"


#define DEBUG_DISP (0)
#define BUILD_ERROR_0418 (0)


namespace ss
{

static u8 blendNumber( u8 a , u8 b , float rate )
{
	return ( a + ( b - a ) * rate );
}

static float blendFloat( float a,float b , float rate )
{
	return   ( a + ( b - a ) * rate );
}

double OutQuad(double t, double totaltime, double max, double min)
{
	if (totaltime == 0.0) return 0.0;

	if (t > totaltime) t = totaltime;
	max -= min;
	t /= totaltime;
	return -max*t*(t - 2) + min;
}

//���ݎ��Ԃ���Y�o�����ʒu�����߂�
//time�ϐ����狁�߂��鎮�Ƃ���
//�p�[�e�B�N�����W�v�Z�̃R�A
void	SsEffectEmitter::updateParticle(float time, particleDrawData* p, bool recalc )
{
	float _t = (float)(time - p->stime);
	float _tm = (float)(_t - 1.0f );
	float _t2 = _t * _t; //(�o�ߎ��Ԃ̓��)
	float _life = (float)( p->lifetime - p->stime);

	if ( _life == 0 ) return ;
	float _lifeper = (float)( _t / _life );


	//_t = 0���_�̒l�����
	//�V�[�h�l�ŌŒ艻����邱�Ƃ��O��
	unsigned long pseed = seedList[p->id % seedTableLen];


	//���g�̃V�[�h�l�A�G�~�b�^�[�̃V�[�h�l�A�e�p�[�e�B�N���̂h�c���V�[�h�l�Ƃ���
	rand.init_genrand((pseed + emitterSeed + p->pid + seedOffset));

	float rad = particle.angle + (rand.genrand_float32() * (particle.angleVariance ) - particle.angleVariance/2.0f);
	//float speed = rand.genrand_float32() * particle.speed;
	float speed = particle.speed + ( particle.speed2 * rand.genrand_float32() );



	//�ڐ������x
	float addr = 0;
	if ( particle.useTanAccel )
	{
		float accel = particle.tangentialAccel + (rand.genrand_float32() * particle.tangentialAccel2);

		float _speed = speed;
		if ( _speed <= 0 )_speed = 0.1f;
		//���ϊp���x�����߂�
		float l = _life * _speed * 0.2f; //�~�̔��a
		float c = 3.14 * l;

		//�ŉ~�� / �����x(pixel)
		addr = ( accel / c ) * _t;
	}

	float x = cos(rad + addr) * speed * (float)_t;
	float y = sin(rad + addr) * speed * (float)_t;

	if ( particle.useTransSpeed )
	{
		float transspeed = particle.transSpeed + ( particle.transSpeed2 * rand.genrand_float32() );
        float speedadd = transspeed / _life;

		float addtx =  cos(rad + addr) * speed;
		float addtx_trans =  cos(rad + addr) * speedadd;

		float addx = (( addtx_trans * _t ) + addtx ) * (_t+1.0f) / 2.0f;


		float addty =  sin(rad + addr) * speed;
		float addty_trans =  sin(rad + addr) * speedadd;

		float addy = (( addty_trans * _t ) + addty ) * ( _t+1.0f) / 2.0f;

		x = addx;
		y = addy;

	}


	//�d�͉����x�̌v�Z
	if ( particle.useGravity )
	{
		x += (0.5 * particle.gravity.x * (_t2));
		y += (0.5 * particle.gravity.y * (_t2));
	}

	//�����ʒu�I�t�Z�b�g
	float ox,oy;
	ox = oy = 0;
	if ( particle.useOffset )
	{
		ox = (particle.offset.x + (particle.offset2.x * rand.genrand_float32()));
		oy = (particle.offset.y + (particle.offset2.y * rand.genrand_float32()));
	}

	//�p�x�����l
	p->rot = 0;
	if ( particle.useRotation )
	{
		p->rot = particle.rotation + (rand.genrand_float32() * particle.rotation2);
		float add = particle.rotationAdd + (rand.genrand_float32() * particle.rotationAdd2);

		//�p�x�ω�
		if ( particle.useRotationTrans )
		{
			//���B�܂ł̐�Ύ���
			float lastt = _life * particle.endLifeTimePer;

			float addf = 0;
			if ( lastt == 0 )
			{
			  	float addrf =  (add * particle.rotationFactor) * _t;
				p->rot+=addrf;
			}else{
				//1�t���[���ŉ��Z������
				addf = (add * particle.rotationFactor - add) / lastt;

				//���܂莞��
				float mod_t = _t - lastt;
				if ( mod_t < 0 ) mod_t = 0;

				//���ݎ��ԁi�ŏI���ԂŃ��~�b�g
				float nowt = _t;
				if ( nowt > lastt ) nowt = lastt;

				//�ŏI�� + ���� x F / 2
				float final_soul = add + addf * nowt;
				float addrf = (final_soul + add) * (nowt + 1.0f) / 2.0f;
				addrf -= add;
				addrf += (mod_t * (final_soul)); //���܂�ƏI���̐ς����Z
				p->rot+=addrf;
			}
		}else{
			p->rot+= ( (add*_t) );
		}
	}

	//�J���[�̏����l�A�J���[�̕ω�
	p->color.a = 0xff;
	p->color.r = 0xff;
	p->color.g = 0xff;
	p->color.b = 0xff;

	if ( particle.useColor)
	{
		p->color.a = particle.initColor.a + (rand.genrand_float32() * particle.initColor2.a );
		p->color.r = particle.initColor.r + (rand.genrand_float32() * particle.initColor2.r );
		p->color.g = particle.initColor.g + (rand.genrand_float32() * particle.initColor2.g );
		p->color.b = particle.initColor.b + (rand.genrand_float32() * particle.initColor2.b );
	}

	if ( particle.useTransColor )
	{
		SsU8Color ecolor;
		ecolor.a = particle.transColor.a + (rand.genrand_float32() * particle.transColor2.a );
		ecolor.r = particle.transColor.r + (rand.genrand_float32() * particle.transColor2.r );
		ecolor.g = particle.transColor.g + (rand.genrand_float32() * particle.transColor2.g );
		ecolor.b = particle.transColor.b + (rand.genrand_float32() * particle.transColor2.b );

		p->color.a = blendNumber( p->color.a , ecolor.a , _lifeper );
		p->color.r = blendNumber( p->color.r , ecolor.r , _lifeper );
		p->color.g = blendNumber( p->color.g , ecolor.g , _lifeper );
		p->color.b = blendNumber( p->color.b , ecolor.b , _lifeper );
	}

	if ( particle.useAlphaFade )
	{

		float start = particle.alphaFade;
		float end = particle.alphaFade2;
        float per = _lifeper * 100.0f;


		if ( per < start )
		{
			float alpha = (start - per) / start;
			p->color.a*= 1.0f - alpha;
		}else{

			if ( per > end )
			{

				if (end>=100.0f)
				{
					p->color.a = 0;
				}else{
					float alpha = (per-end) / (100.0f-end);
                    if ( alpha >=1.0f ) alpha = 1.0f;

					p->color.a*= 1.0f - alpha;
				}
			}
		}
	}


	//�X�P�[�����O
	p->scale.x = 1.0f;
	p->scale.y = 1.0f;
	float scalefactor = 1.0f;

	if ( particle.useInitScale )
	{
		p->scale.x = particle.scale.x + (rand.genrand_float32() * particle.scaleRange.x );
		p->scale.y = particle.scale.y + (rand.genrand_float32() * particle.scaleRange.y );

        scalefactor = particle.scaleFactor + (rand.genrand_float32() * particle.scaleFactor2 );


	}

	if ( particle.useTransScale )
	{
		SsVector2 s2;
		float sf2;
		s2.x = particle.transscale.x + (rand.genrand_float32() * particle.transscaleRange.x );
		s2.y = particle.transscale.y + (rand.genrand_float32() * particle.transscaleRange.y );

		sf2 = particle.transscaleFactor + (rand.genrand_float32() * particle.transscaleFactor2 );

		p->scale.x = blendFloat( p->scale.x , s2.x , _lifeper );
		p->scale.y = blendFloat( p->scale.y , s2.y , _lifeper );
        scalefactor = blendFloat( scalefactor , sf2 , _lifeper );

	}

	p->scale.x*=scalefactor;
	p->scale.y*=scalefactor;

	p->x = x + ox + position.x;//�G�~�b�^����̃I�t�Z�b�g�����Z
	p->y = y + oy + position.y;//�G�~�b�^����̃I�t�Z�b�g�����Z


  	//�w��̓_�ւ悹��
	if ( particle.usePGravity )
	{

		//�����n�_����̋���
		SsVector2 v = SsVector2(  particle.gravityPos.x - (ox + position.x) ,
                         particle.gravityPos.y - (oy + position.y) );


		SsVector2 nv;
		SsVector2::normalize( v , &nv );

		float gp = particle.gravityPower;
		if (gp > 0) {
			SsVector2 v2 = SsVector2(p->x, p->y);
			float len = v.length(); // �����ʒu����̋���
			float et = (len / gp)*0.90f;;

			float _gt = _t;
			if ( _gt >= (int)et )
			{
				_gt = et*0.90f;// + (_t / _life *0.1f);
			}

			nv = nv * gp * _gt;
			p->x += nv.x;
			p->y += nv.y;


			float blend = OutQuad(_gt, et, 0.9f, 0.0f);
			blend = blend; // *gp;
			blend += (_t / _life *0.1f);

			p->x = blendFloat(p->x, particle.gravityPos.x, blend);
			p->y = blendFloat(p->y, particle.gravityPos.y, blend);

		}
		else {
			nv = nv * gp * _t;
			// �p���[�}�C�i�X�̏ꍇ�͒P���ɔ���������
			// �����ɂ�錸���͂Ȃ�
			p->x += nv.x;
			p->y += nv.y;
		}
#if 0
		float gx = OutQuad(_t *0.8f, _life, particle.gravityPos.x, ox + position.x);
		float gy = OutQuad(_t *0.8f, _life, particle.gravityPos.y, oy + position.y);

		float gp = particle.gravityPower;
		if (gp < 0)
		{
			p->x = blendFloat(p->x, -gx, -gp);
			p->y = blendFloat(p->y, -gy, -gp);

		}
		else
		{
			p->x = blendFloat(p->x, gx, gp);
			p->y = blendFloat(p->y, gy, gp);
		}
#endif
	}

    //�O�̃t���[������̕��������
	p->direc = 0.0f;
	if ( particle.useTurnDirec && recalc==false )
	{
		particleDrawData dp;
        dp = *p;

//		if ( time > 0.0f )
		{
			updateParticle(time + 1.0f, &dp, true);
			p->direc =  SsVector2::get_angle_360(
								SsVector2( 1 , 0 ) ,
								SsVector2(p->x - dp.x, p->y - dp.y) ) + DegreeToRadian(90) + DegreeToRadian(particle.direcRotAdd);
		}
	}


}


bool compare_life( emitPattern& left,  emitPattern& right)
{
	if (left.life == right.life)
	{
		if (left.uid < right.uid) return true;
	}
	return left.life < right.life ;
}

void	SsEffectEmitter::precalculate2()
{

	rand.init_genrand( emitterSeed );

	_emitpattern.clear();
	//_lifeExtend.clear();
	_offsetPattern.clear();

	if ( particleExistList == 0 )
	{
		particleExistList = new particleExistSt[emitter.emitmax]; //���݂��Ă���p�[�e�B�N��������v�Z�p�o�b�t�@
	}

	memset( particleExistList , 0 , sizeof(particleExistSt) * emitter.emitmax );

	if ( emitter.emitnum < 1 ) emitter.emitnum = 1;

	int cycle =  (int)(( (float)(emitter.emitmax *emitter.interval)  / (float)emitter.emitnum ) + 0.5f) ;
    int group =  emitter.emitmax / emitter.emitnum;

	int extendsize = emitter.emitmax*LIFE_EXTEND_SCALE;
	if (extendsize < LIFE_EXTEND_MIN) extendsize = LIFE_EXTEND_MIN;

	int shot = 0;
	int offset = particle.delay;
	for (int i = 0; i < emitter.emitmax; i++)
	{
		if (shot >= emitter.emitnum)
		{
			shot = 0;
			offset += emitter.interval;
		}
		_offsetPattern.push_back(offset);
		shot++;
	}

	for (int i = 0; i < extendsize; i++)
	{
		emitPattern e;
		e.uid = i;
		e.life = emitter.particleLife + emitter.particleLife2 * rand.genrand_float32();
		e.cycle = cycle;
		if (e.life > cycle)
		{
			e.cycle = e.life;
		}

		_emitpattern.push_back(e);
	}

	if (seedList != NULL)
	{
		delete[] seedList;
	}

	particleListBufferSize = emitter.emitmax;

	rand.init_genrand((emitterSeed));

	seedTableLen = particleListBufferSize * 3;
	seedList = new unsigned long[seedTableLen];

	//�e�p�[�e�B�N���h�c����Q�Ƃ���V�[�h�l���e�[�u���Ƃ��č쐬����
	for (size_t i = 0; i < seedTableLen; i++)
	{
    	seedList[i] = rand.genrand_uint32();
	}


}



//----------------------------------------------------------------------------------




void SsEffectEmitter::updateEmitter(double _time, int slide)
{
	int onum = _offsetPattern.size();
	int pnum = _emitpattern.size();
	slide = slide * SEED_MAGIC;


	for (int i = 0; i < onum; i++)
	{
		int slide_num = (i + slide) % pnum;

		emitPattern* targetEP = &_emitpattern[slide_num];

		int t = (int)(_time - _offsetPattern[i]);

		particleExistList[i].exist = false;
		particleExistList[i].born = false;

		if (targetEP->cycle != 0)
		{
			int loopnum = t / targetEP->cycle;
			int cycle_top = loopnum * targetEP->cycle;

			particleExistList[i].cycle = loopnum;

			particleExistList[i].stime = cycle_top + _offsetPattern[i];
			particleExistList[i].endtime = particleExistList[i].stime + targetEP->life;// + _lifeExtend[slide_num];

			if ((double)particleExistList[i].stime <= _time && (double)particleExistList[i].endtime > _time)
			{
				particleExistList[i].exist = true;
				particleExistList[i].born = true;
			}

			if (!this->emitter.Infinite)
			{
				if (particleExistList[i].stime >= this->emitter.life) //�G�~�b�^�[���I�����Ă���
				{
					particleExistList[i].exist = false;    //����ĂȂ�

														   //�ŏI�I�Ȓl�Ɍv�Z������ <-���O�v�Z���Ă����Ƃ��������E
					int t = this->emitter.life - _offsetPattern[i];
					int loopnum = t / targetEP->cycle;

					int cycle_top = loopnum * targetEP->cycle;

					particleExistList[i].stime = cycle_top + _offsetPattern[i];

					particleExistList[i].endtime = particleExistList[i].stime + targetEP->life;// + _lifeExtend[slide_num];
					particleExistList[i].born = false;
				}
				else 
				{
					particleExistList[i].born = true;
				}
			}

			if (t < 0) {
				particleExistList[i].exist = false;
				particleExistList[i].born = false;
			}
		}
	}

}



const particleExistSt*	SsEffectEmitter::getParticleDataFromID(int id)
{

	return &particleExistList[id];
}


void	SsEffectRenderV2::drawSprite(
		SsCellValue*		dispCell,
		SsVector2 _position,
		SsVector2 _size,
		float     _rotation,
		float	  direction,
		SsFColor	_color,
		SsRenderBlendType::_enum blendType
	)
{

	if (dispCell->refCell.cellIndex == -1) return;

	float		matrix[4 * 4];	///< �s��
	IdentityMatrix( matrix );

	float parentAlpha = 1.0f;

	if (_parentSprite)
	{
		memcpy( matrix , _parentSprite->_state.mat , sizeof( float ) * 16 );
    	parentAlpha = _parentSprite->_state.opacity / 255.0f;
	}


#ifdef UP_MINUS
	TranslationMatrixM(matrix, _position.x * layoutScale.x, -_position.y * layoutScale.y, 0.0f);	//�オ�}�C�i�X�Ȃ̂Ŕ��]����
#else
	TranslationMatrixM(matrix, _position.x * layoutScale.x, _position.y * layoutScale.y, 0.0f);	//���C�A�E�g�X�P�[���̔��f
#endif

	RotationXYZMatrixM( matrix , 0 , 0 , DegreeToRadian(_rotation)+direction );

    ScaleMatrixM(  matrix , _size.x, _size.y, 1.0f );

	SsFColor fcolor;
	fcolor.fromARGB( _color.toARGB() );
	fcolor.a = fcolor.a * parentAlpha;
	if (fcolor.a == 0.0f)
	{
		return;
	}

	State state;
	state = _parentSprite->_state;		//�e�p�[�c�̏����R�s�[
	for (int i = 0; i < 16; i++)
	{
		state.mat[i] = matrix[i];				//�}�g���N�X�̃R�s�[
	}
	state.cellIndex = dispCell->refCell.cellIndex;
	state.texture = dispCell->refCell.texture;	//�e�N�X�`��ID	
	state.rect = dispCell->refCell.rect;		//�Z���̋�`���R�s�[	
	float width_h = state.rect.size.width / 2;
	float height_h = state.rect.size.height / 2;
	float x1 = -width_h;
	float y1 = -height_h;
	float x2 = width_h;
	float y2 = height_h;

#ifdef UP_MINUS
	state.quad.tl.vertices.x = x1;
	state.quad.tl.vertices.y = y1;
	state.quad.tr.vertices.x = x2;
	state.quad.tr.vertices.y = y1;
	state.quad.bl.vertices.x = x1;
	state.quad.bl.vertices.y = y2;
	state.quad.br.vertices.x = x2;
	state.quad.br.vertices.y = y2;
#else
	state.quad.tl.vertices.x = x1;
	state.quad.tl.vertices.y = y2;
	state.quad.tr.vertices.x = x2;
	state.quad.tr.vertices.y = y2;
	state.quad.bl.vertices.x = x1;
	state.quad.bl.vertices.y = y1;
	state.quad.br.vertices.x = x2;
	state.quad.br.vertices.y = y1;
#endif

	//UV��ݒ肷��
	int atlasWidth = state.texture.size_w;
	int atlasHeight = state.texture.size_h;
	float left, right, top, bottom;
	left = state.rect.origin.x / (float)atlasWidth;
	right = (state.rect.origin.x + state.rect.size.width) / (float)atlasWidth;
	top = state.rect.origin.y / (float)atlasHeight;
	bottom = (state.rect.origin.y + state.rect.size.height) / (float)atlasHeight;

	state.quad.tl.texCoords.u = left;
	state.quad.tl.texCoords.v = top;
	state.quad.tr.texCoords.u = right;
	state.quad.tr.texCoords.v = top;
	state.quad.bl.texCoords.u = left;
	state.quad.bl.texCoords.v = bottom;
	state.quad.br.texCoords.u = right;
	state.quad.br.texCoords.v = bottom;

	//�u�����h�^�C�v��ݒ�
	if (dispCell->blendType == SsRenderBlendType::Mix)
	{
		state.blendfunc = BLEND_MIX;	//�u�����h�^�C�v��ݒ�
	}
	else
	{
		state.blendfunc = BLEND_ADD;	//�u�����h�^�C�v��ݒ�
	}
	//	state.flags = PART_FLAG_COLOR_BLEND;		//�J���[�u�����h�t���O��ݒ�
	state.colorBlendFunc = BLEND_MUL;			//�J���[�u�����h�t���O��Z
	int r = (int)(fcolor.r * 255.0f);			//�J���[�l��ݒ�
	int g = (int)(fcolor.g * 255.0f);
	int b = (int)(fcolor.b * 255.0f);
	int a = (int)(fcolor.a * 255.0f);
	state.quad.tl.colors.r = r;
	state.quad.tl.colors.g = g;
	state.quad.tl.colors.b = b;
	state.quad.tl.colors.a = a;
	state.quad.tr.colors = state.quad.bl.colors = state.quad.br.colors = state.quad.tl.colors;
	state.opacity = a;							//�����x��ݒ�

	state.rotationZ += _rotation + RadianToDegree(direction);		//��]
	state.scaleX *= _size.x;		//�X�P�[��
	state.scaleY *= _size.y;		//�X�P�[��

	if ((state.scaleX * state.scaleY) < 0)	//�X�P�[���̂ǂ��炩��-�̏ꍇ�͉�]�������t�ɂ���
	{
		state.rotationZ = -state.rotationZ;
	}

	//���_�v�Z���s��
	float px = 0;
	float py = 0;
	float cx = ((state.rect.size.width * state.scaleX) * -(dispCell->refCell.pivot_X));
#ifdef UP_MINUS
	float cy = ((state.rect.size.height * state.scaleY) * -(dispCell->refCell.pivot_Y));
#else
	float cy = ((state.rect.size.height * state.scaleY) * +(dispCell->refCell.pivot_Y));
#endif
	get_uv_rotation(&cx, &cy, 0, 0, state.rotationZ);

	state.mat[12] += cx;
	state.mat[13] += cy;

	SSDrawSprite(state);	//�`��

	_drawSpritecount++;
}


void SsEffectRenderV2::particleDraw(SsEffectEmitter* e , double time , SsEffectEmitter* parent , particleDrawData* plp )
{
	double t = time;

	if (e == 0) return;

	int pnum = e->getParticleIDMax();

	int slide = (parent == 0) ? 0 : plp->id;
	e->updateEmitter(time, slide);

	for (auto id = 0; id < pnum; id++)
	{
		const particleExistSt* drawe = e->getParticleDataFromID(id);

        if ( !drawe->born )continue;

		float targettime = (t + 0.0f);
		particleDrawData lp;
		particleDrawData pp;
		pp.x = 0; pp.y = 0;

		lp.id = id + drawe->cycle;
		lp.stime = drawe->stime;
		lp.lifetime = drawe->endtime;
		lp.pid = 0;

		if ( parent )lp.pid = plp->id;

		//if ( lp.stime == lp.lifetime ) continue;

		//if ( lp.stime <= targettime && lp.lifetime >= targettime)
		if ( drawe->exist )
		{

			if (parent)
			{
				//�e����`�悷��p�[�e�B�N���̏����ʒu�𒲂ׂ�
				pp.id = plp->id;
				pp.stime = plp->stime;
				pp.lifetime = plp->lifetime;
				pp.pid = plp->pid;
				//�p�[�e�B�N���������������Ԃ̐e�̈ʒu�����

				int ptime = lp.stime + pp.stime;
				if ( ptime > lp.lifetime ) ptime = lp.lifetime;

				//�t�Z�̓f�o�b�O�����炢��������Ȃ�
				parent->updateParticle( lp.stime + pp.stime , &pp);
				e->position.x = pp.x;
				e->position.y = pp.y;

			}


			e->updateParticle(targettime, &lp);


			SsFColor fcolor;
			fcolor.fromARGB(lp.color.toARGB());

			drawSprite( &e->dispCell ,
						SsVector2(lp.x,lp.y),
						lp.scale,
						lp.rot , lp.direc , fcolor , e->refData->blendType );


		}

	}



}



//�p�����[�^���R�s�[����
void	SsEffectRenderV2::initEmitter( SsEffectEmitter* e , SsEffectNode* node)
{

	e->refData = node->GetMyBehavior();
/*
	e->refCell = e->refData->refCell;

	//�Z���̏�����
	SsCelMapLinker* link = this->curCellMapManager->getCellMapLink( e->refData->CellMapName );

	if ( link )
	{
		SsCell * cell = link->findCell( e->refData->CellName );
		
		getCellValue(	this->curCellMapManager , 
			e->refData->CellMapName ,
			e->refData->CellName , 
			e->dispCell ); 
	}else{
		DEBUG_PRINTF( "cell not found : %s , %s\n" , 
			e->refData->CellMapName.c_str(), 
			e->refData->CellName.c_str()
			);
	}
*/
	e->dispCell.refCell = e->refData->refCell;
	e->dispCell.blendType = e->refData->blendType;

	SsEffectFunctionExecuter::initializeEffect( e->refData , e );

	e->emitterSeed = this->mySeed;

	if ( e->particle.userOverrideRSeed )
	{
		e->emitterSeed = e->particle.overrideRSeed;

	}else{
		if ( this->effectData->isLockRandSeed )
		{
			e->emitterSeed = (this->effectData->lockRandSeed+1) * SEED_MAGIC;
		}
	}

	e->emitter.life+= e->particle.delay;//�f�B���C�����Z
}


void	SsEffectRenderV2::clearEmitterList()
{
	for ( size_t i = 0 ; i < this->emmiterList.size(); i++)
	{
		delete emmiterList[i];
	}

    emmiterList.clear();
	updateList.clear();

}



void	SsEffectRenderV2::setEffectData(SsEffectModel* data)
{
	effectData = data;

    reload();

}


void	SsEffectRenderV2::update()
{

	if ( !m_isPlay ) return;

	targetFrame = nowFrame;

	if ( !this->Infinite )
	{
		if (this->isloop()) //�������[�v�̏ꍇ
		{
			if (nowFrame > getEffectTimeLength())
			{
				targetFrame = (int)((int)nowFrame % getEffectTimeLength());
				int l = (nowFrame / getEffectTimeLength());
				setSeedOffset(l);
			}
		}
	}
}

void	SsEffectRenderV2::draw()
{
	_drawSpritecount = 0;	//�\���X�v���C�g���̃N���A

	if (nowFrame < 0) return;

	for (size_t i = 0; i < updateList.size(); i++)
	{
		SsEffectEmitter* e = updateList[i];
		if (e)
		{
			e->setSeedOffset(seedOffset);
		}
	}

	for ( size_t i = 0 ; i < updateList.size() ; i++ )
	{

		SsEffectEmitter* e = updateList[i];

		if ( e->_parent )
		{
			//�O���[�o���̎��ԂŌ��ݐe���ǂꂾ����������Ă���̂����`�F�b�N����
			e->_parent->updateEmitter(targetFrame, 0);

			int loopnum =  e->_parent->getParticleIDMax();
			for ( int n = 0 ; n < loopnum ; n ++ )
			{
				const particleExistSt* drawe = e->_parent->getParticleDataFromID(n);

				if ( drawe->born )
				{
					particleDrawData lp;
					lp.stime = drawe->stime;
					lp.lifetime = drawe->endtime;
					lp.id = n;
					lp.pid = 0;

					float targettime = (targetFrame + 0.0f);
					float ptime = (targettime - lp.stime );

	  				particleDraw( e , ptime , e->_parent , &lp);
				}
			}

		}else{
			particleDraw( e , targetFrame );
		}
	}

}


bool compare_priority( SsEffectEmitter* left,  SsEffectEmitter* right)
{
	if (left->priority == right->priority)
	{
		if (left->uid < right->uid) return true;
	}
	//	return true;
  return left->priority < right->priority ;
}


void    SsEffectRenderV2::reload()
{
	nowFrame = 0;

	//update���K�v��
	stop();
	clearEmitterList();

	SsEffectNode* root = this->effectData->GetRoot();

	//this->effectData->updateNodeList();//�c�[������Ȃ��̂ŗv��Ȃ�
	const std::vector<SsEffectNode*>& list = this->effectData->getNodeList();

	layoutScale.x = (float)(this->effectData->layoutScaleX) / 100.0f;
	layoutScale.y = (float)(this->effectData->layoutScaleY) / 100.0f;

	int* cnum = new int[list.size()];
	memset(cnum, 0, sizeof(int) * list.size());

	bool _Infinite = false;
	//�p�����[�^���擾
	//�ȑO�̃f�[�^�`������ϊ�
	for (size_t i = 0; i < list.size(); i++)
	{
		SsEffectNode *node = list[i];

		if (node->GetType() == SsEffectNodeType::emmiter)
		{
			SsEffectEmitter* e = new SsEffectEmitter();
			//�p�����[�^���R�s�[

			e->_parentIndex = node->parentIndex;
			//�q����͋��炭�p�[�e�B�N���Ȃ̂ŃG�~�b�^�ɕϊ�
			if (e->_parentIndex != 0)
			{
				e->_parentIndex = list[e->_parentIndex]->parentIndex;

			}

			cnum[e->_parentIndex]++;
			if (cnum[e->_parentIndex] > 10)
			{
				_isWarningData = true;
				continue; //�q�P�O�m�[�h�\������
			}

			//���}���΍�
			if (e->_parentIndex != 0)
			{
				int a = list[e->_parentIndex]->parentIndex;
				if (a != 0)
				{
					if (list[a]->parentIndex > 0) {
						_isWarningData = true;
						continue;
					}
				}
			}

			initEmitter(e, node);
			this->emmiterList.push_back(e);
			if (e->emitter.Infinite) _Infinite = true;
		}
		else
		{
			//�G�~�b�^�[���m���q�������̂�
			this->emmiterList.push_back(0);
		}
	}

	delete[] cnum;
	Infinite = _Infinite;


	//�e�q�֌W����


	effectTimeLength = 0;
	//���O�v�Z�v�Z  updateList�Ƀ��[�g�̎q��z�u���e�q�֌W������
	for (size_t i = 0; i < this->emmiterList.size(); i++)
	{

		if (emmiterList[i] != 0)
		{
			emmiterList[i]->uid = i;
			//emmiterList[i]->precalculate();
			emmiterList[i]->precalculate2(); //���[�v�Ή��`��


			int  pi = emmiterList[i]->_parentIndex;

			if (emmiterList[i]->_parentIndex == 0)  //���[�g����
			{
				emmiterList[i]->_parent = 0;
				emmiterList[i]->globaltime = emmiterList[i]->getTimeLength();
				updateList.push_back(emmiterList[i]);
			}
			else
			{

				void* t = this->emmiterList[pi];

				emmiterList[i]->_parent = emmiterList[pi];

				emmiterList[i]->globaltime = emmiterList[i]->getTimeLength() + this->emmiterList[pi]->getTimeLength();

				updateList.push_back(emmiterList[i]);
			}

			if (emmiterList[i]->globaltime > effectTimeLength)
			{
				effectTimeLength = emmiterList[i]->globaltime;
			}
		}
	}
	//�v���C�I���e�B�\�[�g
	std::sort(updateList.begin(), updateList.end(), compare_priority);


}


size_t  SsEffectRenderV2::getEffectTimeLength()
{

	return effectTimeLength;
}


int	SsEffectRenderV2::getCurrentFPS(){
	if (effectData)
	{
		if ( effectData->fps == 0 ) return 30;

		return effectData->fps;
	}
	return 30;
}

};
