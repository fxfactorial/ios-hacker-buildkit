#line 1 "tweak.xm"
#include <logos/logos.h>
#include <substrate.h>

@class SBLockScreenView;

static void (*_logos_orig$_ungrouped$SBLockScreenView$setCustomSlideToUnlockText$)(SBLockScreenView*, SEL, id);
static void _logos_method$_ungrouped$SBLockScreenView$setCustomSlideToUnlockText$(SBLockScreenView*, SEL, id);

#line 1 "tweak.xm"

static void _logos_method$_ungrouped$SBLockScreenView$setCustomSlideToUnlockText$(SBLockScreenView* self, SEL _cmd, id arg1)
{
  arg1 = @"Changed the slider";
  _logos_orig$_ungrouped$SBLockScreenView$setCustomSlideToUnlockText$(self, _cmd, arg1);
}

static __attribute__((constructor)) void _logosLocalInit()
{
  {
    Class _logos_class$_ungrouped$SBLockScreenView = objc_getClass("SBLockScreenView");
    MSHookMessageEx(_logos_class$_ungrouped$SBLockScreenView, @selector(setCustomSlideToUnlockText:),
		    (IMP)&_logos_method$_ungrouped$SBLockScreenView$setCustomSlideToUnlockText$,
		    (IMP*)&_logos_orig$_ungrouped$SBLockScreenView$setCustomSlideToUnlockText$);
  }
}
#line 8 "tweak.xm"
