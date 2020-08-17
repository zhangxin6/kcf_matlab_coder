
p1 = mfilename('fullpath');
i=findstr(p1,'/');
p1=p1(1:i(end));
cd(p1);
cd('../');
s=dir([pwd '/src']);
fp  = fopen('test.sh','w');
fp2 = fopen('kcfsz.txt','w');
fprintf(fp,"%s\n","cd ..");
for i=3:size(s,1)
  r = regexp(s(i).name,'\.','split');
  if(size(r,1)>=1 && size(r,2)>=2)
    if(r{1,2}=='c')
      f = ["gcc -c src/" s(i).name " -g -O0 -Wall  -o ./Debug/" s(i).name ".o -I. -I."];
      fprintf(fp,"%s",f);
      fprintf(fp,"\n");
    end
  end
end

f = [];
for i=3:size(s,1)
  r = regexp(s(i).name,'\.','split');
  if(size(r,1)>=1 && size(r,2)>=2)
    if(r{1,2}=='c')
        if(strcmp(r{1,1},'main') == 0)
          f= [f './Debug/' s(i).name ".o "];
        end
    end
  end
end
f = [f './Debug/main.c.o'];
fprintf(fp2,"%s",f);
fs = ["gcc -o ./Debug/kcfs " '"@auto_test/kcfsz.txt"' " -L.   -lm -fopenmp"];
fprintf(fp,"%s",fs);
movefile('test.sh', 'auto_test');
movefile('kcfsz.txt', 'auto_test');

fclose(fp);
fclose(fp2);

endl =1
