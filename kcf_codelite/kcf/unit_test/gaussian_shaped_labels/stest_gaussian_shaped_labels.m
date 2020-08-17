function stest_gaussian_shaped_labels(input1,seq)

  fid = fopen(['gaussian_shaped_labels_' num2str(seq) '.txt'],'r');
  A = fscanf(fid,'%f,');

  gt0                 = A(1);
  gt1                 = A(2);
  gt2                 = A(3);
  gt3                 = A(4);
  padding             = A(5);
  ifr                 = A(6);
  cell_size           = A(7);
  lambda              = A(8);
  sigma               = A(9);
  output_sigma_factor = A(10);
  im_w                = A(11);
  im_h                = A(12);
  im_p                = A(13);
  box_w               = A(14);
  box_h               = A(15);
  box_p               = A(16);
  AA                  = A(17);
  BB                  = A(18);
  if(exist('p_def.h'))
    delete('p_def.h');
  end
  create('p_def.h', A);
  delete('mex_gaussian_shaped_labels.mexa64');
  mex('mex_gaussian_shaped_labels.c');
  output_sigma = sqrt(gt2*gt3) * output_sigma_factor / cell_size;
  output1 = gaussian_shaped_labels(output_sigma,[floor(box_h / cell_size) floor(box_w / cell_size)]);
  output2 = mex_gaussian_shaped_labels(input1);
  res = compare(output1,output2);

  fprintf('%s',"gaussian_shaped_labels's testcase ");
  fprintf('%d',uint8(seq));
  if(res == 1)
    fprintf('%s\n'," success");
  else
    fprintf('%s\n'," fail");
  end
