/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* vim: set ts=2 sts=2 et sw=2 tw=80: */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/**
 * compute sticky positioning, both during reflow and when the scrolling
 * container scrolls
 */

#ifndef StickyScrollContainer_h
#define StickyScrollContainer_h

#include "nsPoint.h"
#include "nsTArray.h"
#include "nsIScrollPositionListener.h"

class nsRect;
class nsIFrame;
class nsIScrollableFrame;

namespace mozilla {

class StickyScrollContainer MOZ_FINAL : public nsIScrollPositionListener
{
public:
  /**
   * Find the StickyScrollContainer associated with the scroll container of
   * the given frame, creating it if necessary.
   */
  static StickyScrollContainer* StickyScrollContainerForFrame(nsIFrame* aFrame);

  /**
   * Find the StickyScrollContainer associated with the given scroll frame,
   * if it exists.
   */
  static StickyScrollContainer* GetStickyScrollContainerForScrollFrame(nsIFrame* aScrollFrame);

  void AddFrame(nsIFrame* aFrame) {
    mFrames.AppendElement(aFrame);
  }
  void RemoveFrame(nsIFrame* aFrame) {
    mFrames.RemoveElement(aFrame);
  }

  // Compute the offsets for a sticky position element
  static void ComputeStickyOffsets(nsIFrame* aFrame);

  /**
   * Compute the position of a sticky positioned frame, based on information
   * stored in its properties along with our scroll frame and scroll position.
   */
  nsPoint ComputePosition(nsIFrame* aFrame) const;

  /**
   * Compute and set the position of all sticky frames, given the current
   * scroll position of the scroll frame. If not in reflow, aSubtreeRoot should
   * be null; otherwise, overflow-area updates will be limited to not affect
   * aSubtreeRoot or its ancestors.
   */
  void UpdatePositions(nsPoint aScrollPosition, nsIFrame* aSubtreeRoot);

  // nsIScrollPositionListener
  virtual void ScrollPositionWillChange(nscoord aX, nscoord aY) MOZ_OVERRIDE;
  virtual void ScrollPositionDidChange(nscoord aX, nscoord aY) MOZ_OVERRIDE;

private:
  StickyScrollContainer(nsIScrollableFrame* aScrollFrame);
  ~StickyScrollContainer();

  /**
   * Compute two rectangles that determine sticky positioning: |aStick|, based
   * on the scroll container, and |aContain|, based on the containing block.
   * Sticky positioning keeps the frame position (its upper-left corner) always
   * within |aContain| and secondarily within |aStick|.
   */
  void ComputeStickyLimits(nsIFrame* aFrame, nsRect* aStick,
                           nsRect* aContain) const;

  friend void DestroyStickyScrollContainer(void* aPropertyValue);

  nsIScrollableFrame* const mScrollFrame;
  nsTArray<nsIFrame*> mFrames;
  nsPoint mScrollPosition;
};

} // namespace mozilla

#endif /* StickyScrollContainer_h */
