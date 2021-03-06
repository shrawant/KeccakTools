/*
KeccakTools

The Keccak sponge function, designed by Guido Bertoni, Joan Daemen,
Michaël Peeters and Gilles Van Assche. For more information, feedback or
questions, please refer to our website: http://keccak.noekeon.org/

Implementation by the designers,
hereby denoted as "the implementer".

To the extent possible under law, the implementer has waived all copyright
and related or neighboring rights to the source code in this file.
http://creativecommons.org/publicdomain/zero/1.0/
*/

#ifndef _KECCAKFTRAILCOREROWS_H_
#define _KECCAKFTRAILCOREROWS_H_

#include "Keccak-fPropagation.h"
#include "Keccak-fTrails.h"
#include "progress.h"

/** This class contains a couple of methods to generate 2-round trail cores
  * by exhaustively generating all patterns with 1, 2 or 3 active rows.
  * This is exhaustive up to translation along the z axis.
  */
class KeccakFTrailCoreRows : public KeccakFPropagation
{
protected:
    ProgressMeter progress;
public:
    /** The constructor. See KeccakFPropagation::KeccakFPropagation(). */
    KeccakFTrailCoreRows(const KeccakFDCLC& aParent, KeccakFPropagation::DCorLC aDCorLC);
    /** This method generates all 2-round trail cores up to a given weight,
      * constrained by the number of rows at A=λ<sup>-1</sup>(B) and at B.
      * The maximum number of rows that can be generated by this method is 3,
      * either for A or for B.
      * This is exhaustive up to translation along the z axis.
      * @param  trailsOut   Where to give the produced trails.
      * @param  maxNrRowsAtA    The maximum number of rows at A.
      * @param  maxNrRowsAtB    The maximum number of rows at B.
      * @param  maxWeight   The maximum weight of the 2-round trail core.
      * @pre    @a maxNrRowsAtA ≤ 3 or @a maxNrRowsAtB ≤ 3.
      */
    void generateTrailCoresBasedOnRows(TrailFetcher& trailsOut, int maxNrRowsAtA, int maxNrRowsAtB, unsigned int maxWeight);
    /** This method generates all 2-round trail cores up to a given weight,
      * constrained by the minimum reverse weight at A=λ<sup>-1</sup>(B)
      * and by the weight at B.
      * The maximum (min. rev.) weight that can be generated by this method is 7,
      * either for A or for B.
      * This is exhaustive up to translation along the z axis.
      * @param  trailsOut   Where to give the produced trails.
      * @param  maxMinRevWeightAtA      The maximum mininimum reverse weight at A.
      * @param  maxWeightAtB    The maximum weight at B.
      * @param  maxWeight   The maximum weight of the 2-round trail core.
      * @pre    @a maxMinRevWeightAtA ≤ 7 or @a maxWeightAtB ≤ 7.
      */
    void generateTrailCoresUpToGivenWeight(TrailFetcher& trailsOut, unsigned int maxMinRevWeightAtA, unsigned int maxWeightAtB, unsigned int maxWeight);
protected:
    void generateTrailCoresBasedOnRows(TrailFetcher& trailsOut, bool startingFromA, int maxNrRowsAtA, int maxNrRowsAtB, unsigned int maxWeight);
    void generateTrailCoresUpToGivenWeight(TrailFetcher& trailsOut, bool startingFromA, unsigned int maxMinRevWeightAtA, unsigned int maxWeightAtB, unsigned int maxWeight);
    void filterGeneratedTrailCores(TrailFetcher& trailsOut, const vector<SliceValue>& stateAtAorB, bool stateAtA, unsigned int maxNrRowsAtA, unsigned int maxNrRowsAtB, unsigned int maxWeight);
    void filterGeneratedTrailCoresUpToGivenWeight(TrailFetcher& trailsOut, const vector<SliceValue>& stateAtAorB, bool stateAtA, unsigned int maxMinRevWeightAtA, unsigned int maxWeightAtB, unsigned int maxWeight);
};

#endif
