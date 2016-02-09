%hook SBLockScreenView
-(void)setCustomSlideToUnlockText:(id)arg1
{
  arg1 = @"Changed the slider";
  %orig(arg1);
}
%end
