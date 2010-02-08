from H3DInterface import *

# make sure the device calibration doesn't follow viewpoint
di = getActiveDeviceInfo()
if( di ):
  devices = di.device.getValue()
  for d in devices:
    d.followViewpoint.setValue( False )
