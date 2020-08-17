function stest_ifft(input1,input2,seq)
  delete('mex_fft.mexa64');
  mex('mex_ifft.c');

  output1 = ifft(input1,input2);
  input1 = mex_ifft(input1,input2);


  res = compare(output1,input1);

  fprintf('%s',"ifft's testcase ");
  fprintf('%d',uint8(seq));
  if(res == 1)
    fprintf('%s\n'," success");
  else
    fprintf('%s\n'," fail");
  end
