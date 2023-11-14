/*==============================================================================

   �����蔻�菈�� [collision.cpp]
														 Author :	��������
														 Date   :	2022_11_21	last_update
--------------------------------------------------------------------------------

==============================================================================*/
#include	"main.h"
#include	"collision.h"

#include	<math.h>

//=================================================
//�}�N����`
//=================================================

//=================================================
//�v���g�^�C�v�錾
//=================================================

/*
	�l�p�`���m�̓����蔻��֐�
	in	�l�p�`�P���S���W�A�l�p�`�Q���S���W�A�l�p�`�P�T�C�Y�A�l�p�`�Q�T�C�Y
	out	true:�Փ˂��Ă���		false:�Փ˂��Ă��Ȃ�
*/
bool	CollisionBB(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2)
{
	D3DXVECTOR2	distance = pos2 - pos1;		//�l�p�`�̒��S���W�Ԃ̋���

	D3DXVECTOR2	halfsize1 = size1 * 0.5f;	//�l�p�`1�̃T�C�Y�̔���
	D3DXVECTOR2	halfsize2 = size2 * 0.5f;	//�l�p�`2�̃T�C�Y�̔���

	//X���Ɋւ��āA�l�p�`�T�C�Y�̔����̍��v���A���S���W�Ԃ̋����̐�Βl���傫��������
	if (fabsf(distance.x) < (halfsize1.x + halfsize2.x))
	{
		//Y���Ɋւ��āA�l�p�`�T�C�Y�̔����̍��v���A���S���W�Ԃ̋����̐�Βl���傫��������
		if (fabsf(distance.y) < (halfsize1.y + halfsize2.y))
		{
			//�����Ƃ��������Ă����true��Ԃ�
			return	true;
		}
		else
		{
			return	false;
		}
	}
	else
	{
		return	false;
	}
}
