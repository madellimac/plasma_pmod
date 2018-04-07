----------------------------------------------------------------------------------
--
-- UART_send_V1
-- Version 1.2b.p
-- 
-- V1.2b.p : Update by Camille Monière (2018/04/07) : 
--	  - Try to addapt the controller to the plasma softcore processing unit.
-- V1.2b : Update by Yannick Bornat (2017/10/25)
--    - FIXED : entity mispell
-- V1.2 : Update by Yannick Bornat (2016/07/05)
--    - FIXED : the busy bit depends on unknown signal (meaning that nobody
--      actually used this module for rougly two years :) )
-- V1.1 : Update by Yannick Bornat (2014/08/04)
--    - adapted to fit lab sessions for ENSEIRB-MATMECA
-- V1.0 : Written by Yannick Bornat (2014/01/27)
--
--
-- Sends a char on the UART line
-- during character send, busy output bit is set to '1' and the module ignores inputs.
-- works at 100MHz with 115.200kbps transfer rate or at 50MHz with 9.600kbps tranfer rate.
--
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.numeric_std.all;


entity UART_send is
   Port ( clk    : in  STD_LOGIC;
          reset  : in  STD_LOGIC;
          dat_en : in  STD_LOGIC;
          dat    : in  STD_LOGIC_VECTOR (7 downto 0);
          TX     : out STD_LOGIC;
          busy   : out STD_LOGIC);
end UART_send;

architecture Behavioral of UART_send is

--signal cnt   : integer range 0 to 1023; -- for 100MHz to 115200bps
signal cnt   : integer range 0 to 8192; -- for 50MHz to 9600bps
signal top   : STD_LOGIC;
signal shift : STD_LOGIC_VECTOR (8 downto 0);
signal nbbits: integer range 0 to 15;

begin

top  <= '1' when cnt=0 else '0';
busy <= dat_en when nbbits >= 12 else '1';
TX   <= shift(0);


process(clk)
begin
	if clk'event and clk='1' then
		if reset='1' then
			cnt <= 0;
		elsif nbbits>=12 or cnt=0 then
			--cnt <= 867; -- (100MHz /  115200bps) - 1
			cnt <= 5207; -- (50MHz / 9600bps) -1
		else
			cnt <= cnt-1;
		end if;
	end if;
end process;

process (clk)
begin
	if clk'event and clk='1' then
		if reset='1' then
			shift  <= "111111111";
			nbbits <= 12;
		elsif nbbits>=12 then
			-- this state waits for data to send
			if dat_en='1' then -- data arrives
				shift  <= dat & '0';
				nbbits <= 9;
			end if;
		else
			-- this part actually sends the bits
			if top='1' then
				shift  <= '1' & shift(8 downto 1);
				if nbbits=0 then
				   nbbits <= 15;
				else
				   nbbits <= nbbits -1;
				end if;
			end if;
			
		end if;
	end if;
end process;
end Behavioral;
