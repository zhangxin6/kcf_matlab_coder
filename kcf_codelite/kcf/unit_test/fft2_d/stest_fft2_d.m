function stest_fft2(input1,input2,input3,seq)

  delete('mex_fft2_d.mexa64');
  mex('mex_fft2_d.c');

  output1 = fft2(input1);
  output2 = mex_fft2_d(input1,input2,input3);

  res = compare(output1,output2);

  fprintf('%s',"fft2_d's testcase ");
  fprintf('%d',uint8(seq));
  if(res == 1)
    fprintf('%s\n'," success");
  else
    fprintf('%s\n'," fail");
  end
