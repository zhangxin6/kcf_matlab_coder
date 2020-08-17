function []=init_mexa64()
  p1 = mfilename('fullpath');
  i=findstr(p1,'/');
  p1=p1(1:i(end));
  s=dir([pwd]);

  for i=3:size(s,1)
    r = regexp(s(i).name,'\.','split');
    if(size(r,1)>=1 && size(r,2)>=2)
      if(r{1,2}=='c')
        mex(s(i).name);
      end
    end
  end

  endl = 1
end
