
fid = fopen('cos_32.dat','wb');
N = 32;
for i=0:N-1
  cos_32(i+1) = cos(2*pi*i/N);
end
fwrite(fid,cos_32,'float');
fclose(fid);

fid = fopen('sin_32.dat','wb');
N = 32;
for i=0:N-1
  sin_32(i+1) = sin(2*pi*i/N);
end
fwrite(fid,sin_32,'float');
fclose(fid);

fid = fopen('hann_32.dat','w+');
M =32; N=32;
cos_window = hann(M) * hann(N)';
cos_window = cos_window';
fwrite(fid,cos_window,'float');
fclose(fid);
endl = 1
