


fid = fopen('hann.txt','w+');
M =256; N=128;
cos_window = hann(M) * hann(N)';
for i=1:M
  for j=1:N
    fprintf(fid,'%e,\n',cos_window(i,j));
  end
end
fclose(fid);
endl = 1
