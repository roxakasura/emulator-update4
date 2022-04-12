USE [MuOnline]
GO
/****** Object:  StoredProcedure [dbo].[WZ_GetAccountLevel]    Script Date: 03/30/2022 12:20:36 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

ALTER Procedure [dbo].[WZ_GetAccountLevel]
 @account varchar(10)
AS
BEGIN

SET NOCOUNT ON
SET XACT_ABORT ON

DECLARE @CurrentAccountLevel int
DECLARE @CurrentAccountExpireDate smalldatetime

SELECT @CurrentAccountLevel = AccountLevel, @CurrentAccountExpireDate = AccountExpireDate FROM MEMB_INFO WHERE memb___id = @account

IF (@CurrentAccountLevel <> 0 AND GETDATE() > @CurrentAccountExpireDate)
BEGIN
	SET @CurrentAccountLevel = 0
	UPDATE MEMB_INFO SET AccountLevel = @CurrentAccountLevel, AccountExpireDate = @CurrentAccountExpireDate WHERE memb___id = @account
END

SELECT @CurrentAccountLevel as AccountLevel, @CurrentAccountExpireDate as AccountExpireDate

SET NOCOUNT OFF
SET XACT_ABORT OFF

END
