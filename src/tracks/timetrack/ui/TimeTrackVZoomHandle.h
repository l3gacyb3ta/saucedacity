/**********************************************************************

Audacity: A Digital Audio Editor

TimeTrackVZoomHandle.h

Paul Licameli split from TimeTrackVZoomHandle.h

**********************************************************************/

#ifndef __AUDACITY_TIMETRACK_VZOOM_HANDLE__
#define __AUDACITY_TIMETRACK_VZOOM_HANDLE__

#include "../../../UIHandle.h" // to inherit

class TimeTrack;

class TimeTrackVZoomHandle final : public UIHandle
{
   TimeTrackVZoomHandle(const TimeTrackVZoomHandle&);

public:
   explicit TimeTrackVZoomHandle
      (const std::shared_ptr<TimeTrack> &pTrack, const wxRect &rect, int y);

   TimeTrackVZoomHandle &operator=(const TimeTrackVZoomHandle&) = default;

   ~TimeTrackVZoomHandle() override;

   void Enter( bool forward, SaucedacityProject * ) override;

   Result Click
      (const TrackPanelMouseEvent &event, SaucedacityProject *pProject) override;

   Result Drag
      (const TrackPanelMouseEvent &event, SaucedacityProject *pProject) override;

   HitTestPreview Preview
      (const TrackPanelMouseState &state, SaucedacityProject *pProject)
      override;

   Result Release
      (const TrackPanelMouseEvent &event, SaucedacityProject *pProject,
       wxWindow *pParent) override;

   Result Cancel(SaucedacityProject *pProject) override;

private:
   std::weak_ptr<TimeTrack> mpTrack;
};

#endif