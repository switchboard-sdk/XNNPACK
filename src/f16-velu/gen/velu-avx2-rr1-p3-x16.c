// Auto-generated file. Do not edit!
//   Template: src/f16-velu/avx2-rr1-p3.c.in
//   Generator: tools/xngen
//
// Copyright 2022 Google LLC
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include <assert.h>

#include <immintrin.h>

#include <xnnpack/common.h>
#include <xnnpack/intrinsics-polyfill.h>
#include <xnnpack/vunary.h>


void xnn_f16_velu_ukernel__avx2_rr1_p3_x16(
    size_t batch,
    const void* input,
    void* output,
    const union xnn_f16_elu_params params[restrict XNN_MIN_ELEMENTS(1)])
{
  assert(batch != 0);
  assert(batch % sizeof(uint16_t) == 0);
  assert(input != NULL);
  assert(output != NULL);

  const __m256 vprescale = _mm256_load_ps(params->avx2_rr1_p3.prescale);
  const __m256 vsat_cutoff = _mm256_load_ps(params->avx2_rr1_p3.sat_cutoff);
  const __m256 vmagic_bias = _mm256_load_ps(params->avx2_rr1_p3.magic_bias);
  const __m256 vlog2e = _mm256_load_ps(params->avx2_rr1_p3.log2e);
  const __m256 vminus_ln2 = _mm256_load_ps(params->avx2_rr1_p3.minus_ln2);
  const __m256 vc3 = _mm256_load_ps(params->avx2_rr1_p3.c3);
  const __m256 vc2 = _mm256_load_ps(params->avx2_rr1_p3.c2);
  const __m256 vc1 = _mm256_load_ps(params->avx2_rr1_p3.c1);
  const __m256 valpha = _mm256_load_ps(params->avx2_rr1_p3.alpha);
  const __m256 vbeta = _mm256_load_ps(params->avx2_rr1_p3.beta);

  const uint16_t* i = (const uint16_t*) input;
  uint16_t* o = (uint16_t*) output;
  for (; batch >= 16 * sizeof(uint16_t); batch -= 16 * sizeof(uint16_t)) {
    __m256 vx0 = _mm256_cvtph_ps(_mm_loadu_si128((const __m128i*) i));
    __m256 vx1 = _mm256_cvtph_ps(_mm_loadu_si128((const __m128i*) (i + 8)));
    i += 16;

    const __m256 vz0 = _mm256_max_ps(vsat_cutoff, _mm256_mul_ps(vx0, vprescale));
    const __m256 vz1 = _mm256_max_ps(vsat_cutoff, _mm256_mul_ps(vx1, vprescale));

    __m256 vn0 = _mm256_fmadd_ps(vz0, vlog2e, vmagic_bias);
    __m256 vn1 = _mm256_fmadd_ps(vz1, vlog2e, vmagic_bias);

    __m256 vs0 = _mm256_castsi256_ps(_mm256_slli_epi32(_mm256_castps_si256(vn0), 23));
    vn0 = _mm256_sub_ps(vn0, vmagic_bias);
    __m256 vs1 = _mm256_castsi256_ps(_mm256_slli_epi32(_mm256_castps_si256(vn1), 23));
    vn1 = _mm256_sub_ps(vn1, vmagic_bias);

    __m256 vt0 = _mm256_fmadd_ps(vn0, vminus_ln2, vz0);
    __m256 vt1 = _mm256_fmadd_ps(vn1, vminus_ln2, vz1);

    __m256 vp0 = _mm256_fmadd_ps(vc3, vt0, vc2);
    __m256 vp1 = _mm256_fmadd_ps(vc3, vt1, vc2);

    vp0 = _mm256_fmadd_ps(vp0, vt0, vc1);
    vt0 = _mm256_mul_ps(vt0, valpha);
    vp1 = _mm256_fmadd_ps(vp1, vt1, vc1);
    vt1 = _mm256_mul_ps(vt1, valpha);

    vt0 = _mm256_mul_ps(vt0, vs0);
    vs0 = _mm256_fmsub_ps(vs0, valpha, valpha);
    vt1 = _mm256_mul_ps(vt1, vs1);
    vs1 = _mm256_fmsub_ps(vs1, valpha, valpha);

    const __m256 ve0 = _mm256_fmadd_ps(vp0, vt0, vs0);
    vx0 = _mm256_mul_ps(vx0, vbeta);
    const __m256 ve1 = _mm256_fmadd_ps(vp1, vt1, vs1);
    vx1 = _mm256_mul_ps(vx1, vbeta);

    const __m256 vy0 = _mm256_blendv_ps(vx0, ve0, vx0);
    const __m256 vy1 = _mm256_blendv_ps(vx1, ve1, vx1);

    _mm_storeu_si128((__m128i*) o, _mm256_cvtps_ph(vy0, _MM_FROUND_NO_EXC));
    _mm_storeu_si128((__m128i*) (o + 8), _mm256_cvtps_ph(vy1, _MM_FROUND_NO_EXC));
    o += 16;
  }
  for (; batch >= 8 * sizeof(uint16_t); batch -= 8 * sizeof(uint16_t)) {
    __m256 vx = _mm256_cvtph_ps(_mm_loadu_si128((const __m128i*) i));
    i += 8;

    const __m256 vz = _mm256_max_ps(vsat_cutoff, _mm256_mul_ps(vx, vprescale));

    __m256 vn = _mm256_fmadd_ps(vz, vlog2e, vmagic_bias);
    __m256 vs = _mm256_castsi256_ps(_mm256_slli_epi32(_mm256_castps_si256(vn), 23));
    vn = _mm256_sub_ps(vn, vmagic_bias);
    __m256 vt = _mm256_fmadd_ps(vn, vminus_ln2, vz);

    __m256 vp = _mm256_fmadd_ps(vc3, vt, vc2);
    vp = _mm256_fmadd_ps(vp, vt, vc1);
    vt = _mm256_mul_ps(vt, valpha);
    vt = _mm256_mul_ps(vt, vs);
    vs = _mm256_fmsub_ps(vs, valpha, valpha);
    const __m256 ve = _mm256_fmadd_ps(vp, vt, vs);
    vx = _mm256_mul_ps(vx, vbeta);
    const __m256 vy = _mm256_blendv_ps(vx, ve, vx);

    _mm_storeu_si128((__m128i*) o, _mm256_cvtps_ph(vy, _MM_FROUND_NO_EXC));
    o += 8;
  }
  if XNN_UNLIKELY(batch != 0) {
    assert(batch >= 1 * sizeof(uint16_t));
    assert(batch <= 7 * sizeof(uint16_t));
    __m256 vx = _mm256_cvtph_ps(_mm_loadu_si128((const __m128i*) i));

    const __m256 vz = _mm256_max_ps(vsat_cutoff, _mm256_mul_ps(vx, vprescale));

    __m256 vn = _mm256_fmadd_ps(vz, vlog2e, vmagic_bias);
    __m256 vs = _mm256_castsi256_ps(_mm256_slli_epi32(_mm256_castps_si256(vn), 23));
    vn = _mm256_sub_ps(vn, vmagic_bias);
    __m256 vt = _mm256_fmadd_ps(vn, vminus_ln2, vz);

    __m256 vp = _mm256_fmadd_ps(vc3, vt, vc2);
    vp = _mm256_fmadd_ps(vp, vt, vc1);
    vt = _mm256_mul_ps(vt, valpha);
    vt = _mm256_mul_ps(vt, vs);
    vs = _mm256_fmsub_ps(vs, valpha, valpha);
    const __m256 ve = _mm256_fmadd_ps(vp, vt, vs);
    vx = _mm256_mul_ps(vx, vbeta);
    const __m256 vy = _mm256_blendv_ps(vx, ve, vx);

    __m128i vh = _mm256_cvtps_ph(vy, _MM_FROUND_NO_EXC);
    if (batch & (4 * sizeof(uint16_t))) {
      _mm_storel_epi64((__m128i*) o, vh);
      vh = _mm_unpackhi_epi64(vh, vh);
      o += 4;
    }
    if (batch & (2 * sizeof(uint16_t))) {
      _mm_storeu_si32(o, vh);
      vh = _mm_srli_epi64(vh, 32);
      o += 2;
    }
    if (batch & (1 * sizeof(uint16_t))) {
      *o = (uint16_t) _mm_extract_epi16(vh, 0);
    }
  }
}
