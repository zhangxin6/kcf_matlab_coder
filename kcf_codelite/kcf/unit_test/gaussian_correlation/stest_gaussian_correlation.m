function stest_mul_f(input1,input2,input3,seq)

  fid = fopen(['gaussian_correlation_' num2str(seq) '.txt'],'r');
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
  delete('mex_gaussian_correlation.mexa64');
  mex('mex_gaussian_correlation.c');

  output1 = gaussian_correlation(input1,input2,input3);
  output2 = mex_gaussian_correlation(input1,input2);

  res = compare(output1,output2);

  fprintf('%s',"gaussian_correlation's testcase ");
  fprintf('%d',uint8(seq));
  if(res == 1)
    fprintf('%s\n'," success");
  else
    fprintf('%s\n'," fail");
  end
