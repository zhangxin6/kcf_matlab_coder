function stest_fft2(input1,input2,input3,seq)

  delete('mex_ifft2.mexa64');
  mex('mex_ifft2.c');

  output1 = ifft2(input1);
  output2 = mex_ifft2(input1,input2,input3);

  res = compare(output1,output2);

  fprintf('%s',"ifft2's testcase ");
  fprintf('%d',uint8(seq));
  if(res == 1)
    fprintf('%s\n'," success");
  else
    fprintf('%s\n'," fail");
  end
