function []=para2()
  global gt0
  global gt1
  global gt2
  global gt3
  global padding
  global ifr
  global cell_size
  global lambda
  global sigma
  global output_sigma_factor
  global im_p
  global im_w
  global im_h
  global box_w
  global box_h
  global AA
  global BB
  
  gt0 = 186;
  gt1 = 209;
  gt2 = 45;
  gt3 = 111;
  padding = 1.5;
  ifr     = 0.075;
  cell_size = 1;
  lambda = 0.0001;
  sigma  = 0.2;
  output_sigma_factor = 0.1;
  im_p  = 576*432;
  im_w  = 576;
  im_h  = 432;
  box_w = 128;
  box_h = 256;  
  AA    = 1;
  BB    = 7;
  
end
