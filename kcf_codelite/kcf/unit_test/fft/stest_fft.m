function stest_fft(input1,input2,seq)
  delete('mex_fft.mexa64');
  mex('mex_fft.c');

  output1 = fft(input1,input2);
  input1 = mex_fft(input1,input2);


  res = compare(output1,input1);

  fprintf('%s',"fft's testcase ");
  fprintf('%d',uint8(seq));
  if(res == 1)
    fprintf('%s\n'," success");
  else
    fprintf('%s\n'," fail");
  end
