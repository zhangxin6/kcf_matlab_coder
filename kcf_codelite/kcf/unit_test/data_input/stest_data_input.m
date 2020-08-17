function stest_data_input(input1,input2,seq)

  delete('mex_fft.mexa64');
  mex('mex_data_input.c');

  fid = fopen(input2,'r');
  output1 = fscanf(fid,'%lf,',numel(input1));
  output1 = output1';

  input1 = mex_data_input(input1,input2);

  res = compare(output1,input1);

  fprintf('%s',"data_input's testcase ");
  fprintf('%d',uint8(seq));
  if(res == 1)
    fprintf('%s\n'," success");
  else
    fprintf('%s\n'," fail");
  end
