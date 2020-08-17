function []=create(filename,A)
  fid = fopen(filename,'w+');
  fprintf(fid,'%s',"#define  gt0  ");     fprintf(fid,'%d\n',round(A(1)));
  fprintf(fid,'%s',"#define  gt1  ");     fprintf(fid,'%d\n',round(A(2)));
  fprintf(fid,'%s',"#define  gt2  ");     fprintf(fid,'%d\n',round(A(3)));
  fprintf(fid,'%s',"#define  gt3  ");     fprintf(fid,'%d\n',round(A(4)));
  fprintf(fid,'\n');

  fprintf(fid,'%s',"#define  padding  ");   fprintf(fid,'%f\n',A(5));
  fprintf(fid,'%s',"#define  ift  ");       fprintf(fid,'%f\n',A(6));
  fprintf(fid,'%s',"#define  cell_size  "); fprintf(fid,'%f\n',A(7));
  fprintf(fid,'%s',"#define  lambda  ");    fprintf(fid,'%f\n',A(8));
  fprintf(fid,'%s',"#define  sigma  ");     fprintf(fid,'%f\n',A(9));
  fprintf(fid,'%s',"#define  output_sigma_factor  ");     fprintf(fid,'%f\n',A(10));
  fprintf(fid,'\n');

  fprintf(fid,'%s',"#define  im_w  ");       fprintf(fid,'%d\n',round(A(11)));
  fprintf(fid,'%s',"#define  im_h  ");       fprintf(fid,'%d\n',round(A(12)));
  fprintf(fid,'%s',"#define  im_p  ");       fprintf(fid,'%d\n',round(A(13)));  
  fprintf(fid,'%s',"#define  box_w  ");      fprintf(fid,'%d\n',round(A(14)));
  fprintf(fid,'%s',"#define  box_h  ");      fprintf(fid,'%d\n',round(A(15)));
  fprintf(fid,'%s',"#define  box_p  ");      fprintf(fid,'%d\n',round(A(16)));
  fprintf(fid,'\n');

  fprintf(fid,'%s',"#define  AA  ");      fprintf(fid,'%d\n',round(A(17)));
  fprintf(fid,'%s',"#define  BB  ");      fprintf(fid,'%d\n',round(A(18)));
  fprintf(fid,'\n');

  fprintf(fid,'%s\n',"typedef struct");
  fprintf(fid,'%s\n',"{");
  fprintf(fid,'%s\n',"double re;");
  fprintf(fid,'%s\n',"double im;");
  fprintf(fid,'%s\n',"}creal_T1;");
  fprintf(fid,'\n');

  fprintf(fid,'%s\n',"#ifndef false");
  fprintf(fid,'%s\n',"#define false 0");
  fprintf(fid,'%s\n',"#endif");
  fprintf(fid,'%s\n',"#ifndef true");
  fprintf(fid,'%s\n',"#define true 1");
  fprintf(fid,'%s\n',"#endif");
  fprintf(fid,'\n');

  fprintf(fid,'%s\n',"typedef int  bool1;");
  fprintf(fid,'%s\n',"typedef int  boolean_T1;");
  fclose(fid);
end
