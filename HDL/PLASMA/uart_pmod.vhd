---------------------------------------------------------------------
-- TITLE: UART
-- AUTHOR: Camille Monière (CamilleMVDD@gmail.com)
-- DATE CREATED: 2018/04/07
-- FILENAME: uart_pmod.vhd
-- PROJECT: Plasma CPU core
-- COPYRIGHT: Software placed into the public domain by the author.
--    Software 'as is' without warranty.  Author liable for nothing.  
--    Integrated files (uart_recv and uart_send ) belongs to Yannick Bornat, all rights reserved.
--    
-- DESCRIPTION:
--    Implements the UART for pmod junctions. Uses files designed and written by Yannick Bornat.

---------------------------------------------------------------------
library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_misc.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_textio.all;
use ieee.std_logic_unsigned.all;



entity uart_pmod is
   port(
        clk          : in  std_logic;
        reset        : in  std_logic;
        enable_read  : in  std_logic;
        enable_write : in  std_logic;
        data_in      : in  std_logic_vector(7 downto 0);
        data_out     : out std_logic_vector(7 downto 0);
        uart_read    : in  std_logic;
        uart_write   : out std_logic;
        busy_write   : out std_logic;
        data_avail   : out std_logic);
end; --entity uart_pmod

architecture logic of uart_pmod is   
   component UART_recv 
      Port ( 
             clk    : in  STD_LOGIC;
             reset  : in  STD_LOGIC;
             rx     : in  STD_LOGIC;
             dat    : out STD_LOGIC_VECTOR (7 downto 0);
             dat_en : out STD_LOGIC);
   end component;
   
   signal dat_recv : STD_LOGIC_VECTOR(7 downto 0);
   signal dat_recv_en : STD_LOGIC;
   
   component UART_send 
      Port ( 
             clk    : in  STD_LOGIC;
             reset  : in  STD_LOGIC;
             dat_en : in  STD_LOGIC;
             dat    : in  STD_LOGIC_VECTOR (7 downto 0);
             TX     : out STD_LOGIC;
             busy   : out STD_LOGIC);
   end component;
   
   component my_fifo
      port(
           clk          : in  std_logic;
           reset        : in  std_logic;
           read_en      : in  std_logic;
           write_en     : in  std_logic;
           data_in      : in  std_logic_vector(7 downto 0);
           data_out     : out std_logic_vector(7 downto 0);
           data_avail   : out std_logic);
   end component;
   
begin

unit_recv : UART_recv port map( clk     => clk,
                                reset   => reset,
                                rx      => uart_read,
                                dat     => dat_recv,
                                dat_en  => dat_recv_en
                              );           
                                                  
unit_send : UART_send port map( clk     => clk,
                                reset   => reset,
                                dat_en  => enable_write,
                                dat     => data_in,
                                TX      => uart_write,
                                busy    => busy_write
                              );
                              
unit_fifo_recv : my_fifo port map(    clk           => clk,
                                      reset         => reset,
                                      read_en       => enable_read,
                                      write_en      => dat_recv_en,
                                      data_in       => dat_recv,
                                      data_out      => data_out,
                                      data_avail    => data_avail
                                  );
  
end; --architecture logic

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.numeric_std.all;

entity my_fifo is
   generic (FIFO_LENGTH : integer range 0 to 127 := 32
   );
   port(
        clk          : in  std_logic;
        reset        : in  std_logic;
        read_en      : in  std_logic;
        write_en     : in  std_logic;
        data_in      : in  std_logic_vector(7 downto 0);
        data_out     : out std_logic_vector(7 downto 0);
        data_avail   : out std_logic);
end; --entity my_fifo

architecture logic of my_fifo is
   type reg is array (0 to FIFO_LENGTH-1) of std_logic_vector(7 downto 0);
   
   signal fifo : reg;
   signal sempty, sfull, looped : STD_LOGIC;
   signal head, tail : integer range 0 to FIFO_LENGTH-1;

begin

fifo_operation : process(clk)
begin
    if rising_edge(clk) then
        if reset = '1' then
            head <= 0;
            tail <= 0;
            looped <= '0';
        else
            if write_en = '1' then
                if looped = '0' or head /= tail then
                    fifo(tail) <= data_in;
                    if tail = FIFO_LENGTH-1 then
                        looped <= '1';
                        tail <= 0;
                    else
                        tail <= tail + 1;
                    end if;
                end if;
            end if;
            
            if read_en = '1' then
                if looped = '1' or head /= tail then
                    if head = FIFO_LENGTH-1 then
                        looped <= '0';
                        head <= 0;
                    else
                        head <= head + 1;
                    end if;
                end if;
            end if;
                
        end if;
    end if;
end process fifo_operation;

asynchrone : process(head, tail, looped)
begin
    if head = tail then
        if looped = '1' then
            sfull <= '1';
            sempty <= '0';
        else
            sfull <= '0';
            sempty <= '1';
        end if;
    else
        sfull <= '0';
        sempty <= '0';
    end if;
end process asynchrone;

   data_out <= fifo(head);   
   data_avail <= not sempty;
   
end;
