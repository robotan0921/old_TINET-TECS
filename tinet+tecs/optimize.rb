#
#  TECS Generator
#      Generator for TOPPERS Embedded Component System
#  
#   Copyright (C) 2008-2012 by TOPPERS Project
#--
#   �嵭����Ԥϡ��ʲ���(1)��(4)�ξ������������˸¤ꡤ�ܥ��եȥ���
#   �����ܥ��եȥ���������Ѥ�����Τ�ޤࡥ�ʲ�Ʊ���ˤ���ѡ�ʣ������
#   �ѡ������ۡʰʲ������ѤȸƤ֡ˤ��뤳�Ȥ�̵���ǵ������롥
#   (1) �ܥ��եȥ������򥽡��������ɤη������Ѥ�����ˤϡ��嵭������
#       ��ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ��꤬�����Τޤޤη��ǥ���
#       ����������˴ޤޤ�Ƥ��뤳�ȡ�
#   (2) �ܥ��եȥ������򡤥饤�֥������ʤɡ�¾�Υ��եȥ�������ȯ�˻�
#       �ѤǤ�����Ǻ����ۤ�����ˤϡ������ۤ�ȼ���ɥ�����ȡ�����
#       �ԥޥ˥奢��ʤɡˤˡ��嵭�����ɽ�����������Ѿ�浪��Ӳ���
#       ��̵�ݾڵ����Ǻܤ��뤳�ȡ�
#   (3) �ܥ��եȥ������򡤵�����Ȥ߹���ʤɡ�¾�Υ��եȥ�������ȯ�˻�
#       �ѤǤ��ʤ����Ǻ����ۤ�����ˤϡ����Τ����줫�ξ�����������
#       �ȡ�
#     (a) �����ۤ�ȼ���ɥ�����ȡ����Ѽԥޥ˥奢��ʤɡˤˡ��嵭����
#         �ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ����Ǻܤ��뤳�ȡ�
#     (b) �����ۤη��֤��̤�������ˡ�ˤ�äơ�TOPPERS�ץ������Ȥ�
#         ��𤹤뤳�ȡ�
#   (4) �ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������뤤���ʤ�»
#       ������⡤�嵭����Ԥ����TOPPERS�ץ������Ȥ����դ��뤳�ȡ�
#       �ޤ����ܥ��եȥ������Υ桼���ޤ��ϥ���ɥ桼������Τ����ʤ���
#       ͳ�˴�Ť����ᤫ��⡤�嵭����Ԥ����TOPPERS�ץ������Ȥ�
#       ���դ��뤳�ȡ�
#  
#   �ܥ��եȥ������ϡ�̵�ݾڤ��󶡤���Ƥ����ΤǤ��롥�嵭����Ԥ�
#   ���TOPPERS�ץ������Ȥϡ��ܥ��եȥ������˴ؤ��ơ�����λ�����Ū
#   ���Ф���Ŭ������ޤ�ơ������ʤ��ݾڤ�Ԥ�ʤ����ޤ����ܥ��եȥ���
#   �������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������������ʤ�»���˴ؤ��Ƥ⡤��
#   ����Ǥ�����ʤ���
#  
#   $Id: optimize.rb 1725 2012-05-03 05:29:24Z okuma-top $
#++

class Namespace

  #===  �ƥ���� ID �������͡ˤ���դ���
  def set_cell_id
    # celltype �γƥ���� ID ����դ���
    @celltype_list.each { |t|
      t.set_cell_id
    }

    # ���֥͡��ॹ�ڡ����γƥ���� ID ����դ���
    @namespace_list.each { |n|
      n.set_cell_id
    }
  end

  def optimize
    # celltype �κ�Ŭ��
    @celltype_list.each { |t|
      t.optimize
    }

    # ���֥͡��ॹ�ڡ����κ�Ŭ��
    @namespace_list.each { |n|
      n.optimize
    }
  end

  def reset_optimize
    # celltype �κ�Ŭ��
    @celltype_list.each { |t|
      t.reset_optimize
    }

    # ���֥͡��ॹ�ڡ����κ�Ŭ��
    @namespace_list.each { |n|
      n.reset_optimize
    }
  end
end

class Celltype

  ID_BASE = 1               # reset_optimize �ǥꥻ�åȤ���
  @@ID_BASE = ID_BASE

  #=== �ƥ���� ID �������͡ˤ���դ���
  def set_cell_id

    if $verbose then
      print( "=== id for the cells of celltype #{get_namespace_path.to_s} ===\n" ) 
    end

    if $unique_id then
      @id_base = @@ID_BASE   # id �򥷥��ƥ����Τ�Ϣ�֤ˤ���
    else
      @id_base = 1           # base ���� 1 ����Ϥ��
    end

    id_specified_cells = []
    no_id_specified_cells = []

    # �ץ�ȥ����פ�������������
    @cell_list.each{ |c|
      if c.is_generate? then
        # c.set_id( @id_base + @n_cell_gen )
        id = c.get_specified_id
        if id then
          id_specified_cells << c
        else
          no_id_specified_cells << c
        end
        
        # p "#{c.get_name} #{@id_base+@n_cell_gen}"
        @@ID_BASE     += 1
        @n_cell_gen   += 1
      end
    }

    @ordered_cell_list = []   # id = 1 ��ź�� 0 �˳�Ǽ�����
    # ID ���ꤵ��Ƥ��륻��� id �ֹ��Ϳ����
    id_specified_cells.each{ |c|
      id = c.get_specified_id
      if id > 0 then
        if id >= @n_cell_gen then
          cdl_error( "S9999 $1: id too large $2 (max=$3)", c.get_name, id, @n_cell_gen )
          next
        end
      else
        if - id >= @n_cell_gen then
          cdl_error( "S9999 $1: id too large $2 (max=$3)", c.get_name, id, @n_cell_gen )
          next
        end
        id = @n_cell_gen + id + 1
      end

      if @ordered_cell_list[ id - 1 ] then
        cdl_error( "S9999 $1: id number '$2' conflict with $3", c.get_name, id, @ordered_cell_list[ id - 1 ].get_name )
      end
      @ordered_cell_list[ id - 1 ] = c
      # �̤��ֹ�Ȥ�����Τ��� @id_base ��ä���
      c.set_id( @id_base - 1 + id )
      if $verbose then
        print( "#{c.get_name}: id=#{c.get_id}  specified id=#{c.get_specified_id}\n" )
      end
    }

    # ID ���ꤵ��Ƥ��ʤ������ id �ֹ��Ϳ����
    i = 0
    no_id_specified_cells.each{ |c|
      while( @ordered_cell_list[i] != nil )
        i += 1
      end
      @ordered_cell_list[ i ] = c
      c.set_id( @id_base + i )
      if $verbose then
        print( "#{c.get_name}: id=#{c.get_id}\n" )
      end
    }
    if @n_cell_gen >0 && i >= @n_cell_gen then
      raise "id over id=#{i} N=#{@n_cell_gen}"
    end

  end

  def optimize

    # port �λ��Ȥ��륻�륿���פο�������ο������
    if $verbose then
      print "=== optimizing celltype #{get_namespace_path.to_s} ===\n"
    end

    @port.each{ |port|
      next if port.get_port_type != :CALL

      # add
      # CelltypeName �� PortName �Τߺ�Ŭ���򥹥��å�
      if @name == :"tTest" && port.get_name == :"cREP4" then
        next
      end
      if @name == :"tTest" && port.get_name == :"cREP4_001" then
        next
      end
      if @name == :"tTest" && port.get_name == :"ciTask" then
        next
      end      
      if @name == :"tTCPCEP" && port.get_name == :"cREP4" then
        next
      end
     if @name == :"tUDPCEP" && port.get_name == :"cCallingSendTask" then
        next
      end
      if @name == :"tUDPCEP" && port.get_name == :"cCallingReceiveTask" then
        next
      end
      if @name == :"tTCPCEP" && port.get_name == :"cCallingSendTask" then 
        next
      end      
      if @name == :"tTCPCEP" && port.get_name == :"cCallingReceiveTask" then
        next
      end
      if @name == :"tNeworkTimer" && port.get_name == :"cTCPTask" then
        next
      end
      if @name == :"tEthernetInputTaskBody" && port.get_name == :"cTaskNetworkTimer" then
        next
      end
      if @name == :"tEthernetInputTaskBody" && port.get_name == :"cTaskEthernetOutput" then
        next
      end
      if $verbose then
        print "optimizing port : #{port.get_name}\n"
      end

      port_cells = []    # �Ƥ��襻��
      port_ports = []    # �Ƥ���Υݡ���

      # ����λ��Ȥ��륻��򽸤��ʥݡ��Ȥ���˽�����
      @cell_list.each{ |cell|

        if ! cell.is_generate? then
          next
        end

        jl = cell.get_join_list
        j = jl.get_item( port.get_name )

        if j then
          if j.get_array_member2 then
            # �ƤӸ�����ξ�硢�����η����򽸤��
            j.get_array_member2.each { |j2|
              if j2 then
                port_cells << j2.get_rhs_cell
                port_ports << j2.get_rhs_port   # ���դΥݡ���
              else
                # optional �ǡ�����ź���Τ߽��������Ƥ��ʤ��ʤ��٤ƽ��������ʤ����ϡ�����
                port_cells << nil
                port_ports << nil
              end
            }
          else
            # ���Ƥη����򽸤��
            port_cells << j.get_rhs_cell
            port_ports << j.get_rhs_port   # ���դΥݡ���
          end
        else
          # optional �ǽ��������Ƥ��ʤ���nil �����Ǥ˲ä��Ƥ�����
          port_cells << nil
          port_ports << nil   # ���դΥݡ���
        end
      }

      # ��ʣ���Ǥ������
      port_cells.uniq!
      port_ports.uniq!

      # �ƤӸ��θƤ��褬��ĤΥݡ��Ȥ�������
      if port_ports.length == 1 then

        # �ƤӸ����󤬲���Ĺ�ξ�硢��Ŭ�����ʤ�
             # mikan �ƤӸ��������ǿ��ޥ����Զ������к�
             # ���˾�ޤ��������ϡ��������ؤΥݥ��󥿤Ͼ�ά���뤬������Ŀ��Ͻ��Ϥ���(#_CP_#, #_TCP_#)
             # ���������Ŀ���������Ǥ���ΤǤ���С�����ޥ������� (#_NCPA_#)
        next if port.get_array_size == "[]"

        # �ƤӸ���Ŭ���»�
        @b_cp_optimized = true

        # �Ƥ��褬��ĤΥ����������
        if port_cells.length == 1 then

          # �ƤӸ��� optional �ǽ��������Ƥ��ʤ����ޤ��ϼ�����������ǤϤʤ�����
          if port_ports[0] == nil || port_ports[0].get_array_size == nil then

            @n_call_port_omitted_in_CB += 1               # CB �Ǿ�ά����ƤӸ�
            port.set_cell_unique                          # �����Ĥ�����Ŭ��
            port.set_skelton_useless                      # ������ȥ�ؿ����׺�Ŭ��
            port.set_VMT_useless                          # VMT ���׺�Ŭ�� (ľ�ܼ������ؿ���ƽФ�)

            if $verbose then
              print "cell_unique, VMT_useless & skelton_useless optimize\n"
            end
          else
            port.set_VMT_useless                          # VMT ���׺�Ŭ�� (������ȥ�ؿ���ƽФ�)

            if $verbose then
              print "VMT_useless optimize\n"
            end
          end

        else  # �Ƥ��褬ʣ���Υ����ñ��Υݡ��ȡ�

          # �ƤӸ��� optional �ǽ��������Ƥ��ʤ����ޤ��ϼ�����������ǤϤʤ�����
          if port_ports[0] == nil || port_ports[0].get_array_size == nil then
            if ! @singleton then
              port.set_skelton_useless                    # ������ȥ�ؿ����׺�Ŭ��
              port.set_VMT_useless                        # VMT ���׺�Ŭ�� (������ȥ�ؿ� or �������ؿ���ƽФ�)

              if $verbose then
                print "VMT_useless & skelton useless optimize\n"
              end
            else
              port.set_VMT_useless                           # VMT ���׺�Ŭ�� (������ȥ�ؿ� or �������ؿ���ƽФ�)

              if $verbose then
                print "VMT_useless optimize\n"
              end
            end
          end
        end

        port.set_only_callee( port_ports[0], port_cells[0] )
           # set_cell_unique �Ǥʤ���� cell �ϰ�̣���ʤ�

      end

      # debug
      dbgPrint "#{port.get_name} : # of cells : #{port_cells.length}  # of ports : #{port_ports.length}\n"
    }

    # ��������Ŭ��������
    @port.each{ |port|
      next if port.get_port_type != :CALL



      # �ƤӸ�¦�κ�Ŭ������
      b_VMT_useless     = port.is_VMT_useless?
      b_skelton_useless = port.is_skelton_useless?

      # ����λ��Ȥ��륻��򽸤��ʥݡ��Ȥ���˽�����
      @cell_list.each{ |cell|

        if ! cell.is_generate? then
          next
        end

        jl = cell.get_join_list
        j = jl.get_item( port.get_name )

        if j then    # optional �Ƿ�礵��Ƥ��ʤ���� nil
          if j.get_array_member2 then
            # �ƤӸ�����
            j.get_array_member2.each { |j2|
              if j2 then
                port2 = j2.get_rhs_port   # ���դΥݡ���
                # ������¦�κ�Ŭ����ǽ��������
                port2.set_entry_VMT_skelton_useless( b_VMT_useless, b_skelton_useless )
              #else
              #  optional �ǸƤӸ��������Ǥ����������Ƥ��ʤ�
              end
            }
          else
            port2 = j.get_rhs_port      # ���դΥݡ���
            # ������¦�κ�Ŭ����ǽ��������
            port2.set_entry_VMT_skelton_useless( b_VMT_useless, b_skelton_useless )
          end
        end
      }
    }
  end

  #Celltype# �ꥻ�åȤ���
  def reset_optimize
    @@ID_BASE = ID_BASE      # �����ϰ������Ǥ褤
    @id_base = 1             # set_cell_id �ǥꥻ�åȤ����Τ�����

    @b_cp_optimized = false  # �ƤӸ���Ŭ��
    @n_call_port_omitted_in_CB = 0 # �ƤӸ���Ŭ���ˤ���������Ȥʤä��ݡ��Ȥο�
    @n_cell_gen = 0          # ��������Ŀ�
    @port.each{ |p|
      p.reset_optimize
    }
    @included_header = {}
  end

  #Celltype# �إå��� include ����Ƥ��뤫
  #hname::Symbol : �إå�̾
  #RETURN:: bool_t: false ���󥯥롼�ɤ���Ƥ��ʤ���true ���󥯥롼�ɤ���Ƥ���
  # #_ISH_#, #_ICT_# �ǥإå��������ޤ�Ƥ��뤫�����å�����
  # false ���֤ä���硢hname ����Ͽ����ơ�����θƤӽФ��Ǥ� true ���֤�
  def header_included?( hname )
    if @included_header[ hname ] == nil then
      @included_header[ hname ] = true
      return false
    else
      return true
    end
  end
end


